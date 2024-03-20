#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Taken from stack overflow: https://stackoverflow.com/a/1841775
void removePunctAndLowerStr(char* p) {
    char* src = p, * dst = p;

    while (*src) {
        if (ispunct((unsigned char)*src))  {
            /* Skip this character */
            src++;
        } else if (isupper((unsigned char)*src)) {
            /* Make it lowercase */
            *dst++ = tolower((unsigned char)*src);
            src++;
        } else if (src == dst)  {
            /* Increment both pointers without copying */
            src++;
            dst++;
        } else {
            /* Copy character */
            *dst++ = *src++;
        }
    }

    *dst = 0;
}

FILE* output_file;
pthread_mutex_t file_lock;

typedef struct SpellingMistakes {
    int total_mistake_count;
    int unique_count;
    int capacity;
    char** words;
    int* word_counts;
} SpellingMistakes;

void initSpellingMistakes(SpellingMistakes* spelling_mistakes) {
    spelling_mistakes->total_mistake_count = 0;
    spelling_mistakes->unique_count = 0;
    spelling_mistakes->capacity = 1;
    spelling_mistakes->words = malloc(spelling_mistakes->capacity * sizeof(char*));
    spelling_mistakes->word_counts = malloc(spelling_mistakes->capacity * sizeof(int));
}

// Release all resources accociated with spelling mistakes
void deinitSpellingMistakes(SpellingMistakes* spelling_mistakes) {
    for (int i = 0; i < spelling_mistakes->unique_count; i++) {
        free(spelling_mistakes->words[i]);
    }
    free(spelling_mistakes->words);
    free(spelling_mistakes->word_counts);
}

void checkOrIncreaseWordCapacitySpellingMistakes(SpellingMistakes* spelling_mistakes) {
    // Increases capacity of the spelling mistakes arrays if the capacity has been reached.
    if (spelling_mistakes->unique_count == spelling_mistakes->capacity) {
        spelling_mistakes->capacity *= 2;
        char** temp = malloc(spelling_mistakes->capacity * sizeof(char*));
        int* temp_count = malloc(spelling_mistakes->capacity * sizeof(int));
        for (int i = 0; i < spelling_mistakes->unique_count; i++) {
            temp[i] = spelling_mistakes->words[i];
            temp_count[i] = spelling_mistakes->word_counts[i];
        }
        free(spelling_mistakes->words);
        free(spelling_mistakes->word_counts);
        spelling_mistakes->words = temp;
        spelling_mistakes->word_counts = temp_count;
    }
}

void addOrIncrementWordSpellingMistakes(SpellingMistakes* spelling_mistakes, char* word, int count) {
    for (int i = 0; i < spelling_mistakes->unique_count; i++) {
        if (strcmp(spelling_mistakes->words[i], word) == 0) {
            spelling_mistakes->word_counts[i] += count;
            spelling_mistakes->total_mistake_count += count;
            return;
        }
    }

    // New word that doesn't exist yet
    spelling_mistakes->total_mistake_count += count;
    spelling_mistakes->word_counts[spelling_mistakes->unique_count] = count;
    spelling_mistakes->words[spelling_mistakes->unique_count++] = strdup(word);

    checkOrIncreaseWordCapacitySpellingMistakes(spelling_mistakes);
}

void mergeSpellingMistakes(SpellingMistakes* a, SpellingMistakes* b) {
    // Merge B into A
    for (int i = 0; i < b->unique_count; i++) {
        addOrIncrementWordSpellingMistakes(a, b->words[i], b->word_counts[i]);
    }
}

// Simple bubble sort for sorting by greatest count of each spelling mistake
void sortSpellingMistakes(SpellingMistakes* spelling_mistakes) {
    for (int i = 0; i < spelling_mistakes->unique_count; i++) {
        for (int j = i + 1; j < spelling_mistakes->unique_count; j++) {
            if (spelling_mistakes->word_counts[j - 1] < spelling_mistakes->word_counts[j]) {
                int tmp = spelling_mistakes->word_counts[j - 1];
                spelling_mistakes->word_counts[j - 1] = spelling_mistakes->word_counts[j];
                spelling_mistakes->word_counts[j] = tmp;

                char* tmp_2 = spelling_mistakes->words[j - 1];
                spelling_mistakes->words[j - 1] = spelling_mistakes->words[j];
                spelling_mistakes->words[j] = tmp_2;
            }
        }
    }
}



void* spell_check(void* args) {
    // Decode the thread inputs
    char* dictionary_path = ((char**)args)[0];
    char* input_path = ((char**)args)[1];

    char input_word[512] = {};

    // Open the dictionary file & error check
    FILE* dict_file = fopen(dictionary_path, "r");
    if (dict_file == NULL) {
        printf("Unable to open %s!\n", dictionary_path);
        pthread_exit(NULL);
    }

    int dictionary_length = 0;
    int dictionary_capacity = 1;
    char** dictionary_words = malloc(dictionary_capacity * sizeof(char*));
    while (fscanf(dict_file, "%s\n", input_word) == 1) {
        // Clean the input string and add it to the dictionary list
        removePunctAndLowerStr(input_word);
        dictionary_words[dictionary_length++] = strdup(input_word);
        memset(input_word, 0, 512);

        // Reached capacity of our array - add space.
        if (dictionary_length == dictionary_capacity) {
            dictionary_capacity *= 2;
            char** temp = malloc(dictionary_capacity * sizeof(char*));
            for (int i = 0; i < dictionary_length; i++) {
                temp[i] = dictionary_words[i];
            }
            free(dictionary_words);
            dictionary_words = temp;
        }
    }
    fclose(dict_file);

    // Open the input file & error check
    FILE* input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        printf("Unable to open %s!\n", input_path);
        pthread_exit(NULL);
    }

    SpellingMistakes* spelling_mistakes = malloc(sizeof(SpellingMistakes));
    initSpellingMistakes(spelling_mistakes);
    while (fscanf(input_file, "%s\n", input_word) == 1) {
        // Remove special characters and check if the word is in the dictionary
        removePunctAndLowerStr(input_word);
        for (int i = 0; i < dictionary_length; i++) {
            if (strcmp(dictionary_words[i], input_word) == 0) {
                addOrIncrementWordSpellingMistakes(spelling_mistakes, input_word, 1);
                break;
            }
        }
        memset(input_word, 0, 512);
    }
    fclose(input_file);

    // Sort the spelling mistakes by greatest to least count for easy printing.
    sortSpellingMistakes(spelling_mistakes);

    // Print out the summary to the output file while the lock is active
    pthread_mutex_lock(&file_lock);
    if (spelling_mistakes->unique_count == 0) {
        fprintf(output_file, "%s %d %s %s %s\n", input_path, spelling_mistakes->total_mistake_count, "", "", "");
    }
    else if (spelling_mistakes->unique_count == 1) {
        fprintf(output_file, "%s %d %s %s %s\n", input_path, spelling_mistakes->total_mistake_count, spelling_mistakes->words[0], "", "");
    }
    else if (spelling_mistakes->unique_count == 2) {
        fprintf(output_file, "%s %d %s %s %s\n", input_path, spelling_mistakes->total_mistake_count, spelling_mistakes->words[0], spelling_mistakes->words[1], "");
    }
    else {
        fprintf(output_file, "%s %d %s %s %s\n", input_path, spelling_mistakes->total_mistake_count, spelling_mistakes->words[0], spelling_mistakes->words[1], spelling_mistakes->words[2]);
    }
    pthread_mutex_unlock(&file_lock);

    for (int i = 0; i < dictionary_length; i++) {
        free(dictionary_words[i]);
    }
    free(dictionary_words);

    return (void*)spelling_mistakes;
}


int main(int argc, char* argv[]) {
    // Parse CLI
    int display_summary = 1;
    if (argc > 2) {
        printf("Too many arguments, terminating...\n");
        return -1;
    }
    else if (argc == 2) {
        if (strcmp(argv[1], "-l") != 0) {
            printf("Unknown argument, terminating...\n");
            return -1;
        }
        display_summary = 0;
    }

    int num_of_threads = 1;
    pthread_t* threads = malloc(num_of_threads * sizeof(pthread_t));

    // Open shared output file
    output_file = fopen("dhart04_A2.out", "w");

    // Main menu
    while (1) {
        int main_menu_choice = 2;
        printf("1. Start a new spellchecking task\n");
        printf("2. Exit\n");
        if (scanf("%d", &main_menu_choice) != 1) {
            printf("Invalid input...\n");
            // Clear the input buffer
            while(getchar() != '\n');
            continue;
        }

        if (main_menu_choice < 1 || main_menu_choice > 2) {
            printf("Invalid selection: %d...\n", main_menu_choice);
            continue;
        }

        if (main_menu_choice == 2) {
            printf("Exiting program...\n");
            break;
        }

        // Spellcheck task submenu
        while (1) {
            int sub_menu_choice = 2;
            printf("1. Start a new spellchecking task\n");
            printf("2. Return to main menu\n");
            if (scanf("%d", &sub_menu_choice) != 1) {
                printf("Invalid input...\n");
                // Clear the input buffer
                while(getchar() != '\n');
                continue;
            }

            if (sub_menu_choice < 1 || sub_menu_choice > 2) {
                printf("Invalid selection: %d...\n", sub_menu_choice);
                continue;
            }

            if (sub_menu_choice == 2) {
                printf("Returning to main menu...\n");
                break;
            }

            // Here we get the user input for the dictionary and input filepaths
            while (1) {
                char dictionary_filepath[4096] = {};
                printf("Enter dictionary filepath: ");
                if (scanf("%4095s", dictionary_filepath) != 1) {
                    printf("Invalid input...\n");
                    continue;
                }

                char input_filepath[4096] = {};
                printf("Enter input filepath: ");
                if (scanf("%4095s", input_filepath) != 1) {
                    printf("Invalid input...\n");
                    continue;
                }

                // The input args to a pthread is a void*, so we need to combine our arguments into a pointer (an array will decay to a pointer)
                char* input_args[2] = { dictionary_filepath, input_filepath };
                pthread_create(&threads[0], NULL, spell_check, input_args);

                // Reallocate the thread array and shuffle active threads over so that threads[0] is always empty in prep for the next thread spawn.
                num_of_threads++;
                pthread_t* temp = malloc(num_of_threads * sizeof(pthread_t));
                for (int i = 1; i < num_of_threads; i++) {
                    temp[i] = threads[i - 1];
                }
                free(threads);
                threads = temp;

                break;
            }
            break;
        }

    }

    // Join together all running/completed threads and compile all of their results together
    SpellingMistakes global_mistakes;
    initSpellingMistakes(&global_mistakes);
    for (int i = 1; i < num_of_threads; i++) {
        SpellingMistakes* local_mistakes;
        pthread_join(threads[i], (void**)&local_mistakes);
        if (local_mistakes == NULL) { // If this was reached the thread returned with an error
            continue;
        }
        mergeSpellingMistakes(&global_mistakes, local_mistakes);
        deinitSpellingMistakes(local_mistakes);
        free(local_mistakes);
    }


    if (display_summary) {
        // Sort the spelling mistakes by count so that we can easily display the summary
        sortSpellingMistakes(&global_mistakes);

        // Print the summary
        printf("Number of files processed: %d\n", num_of_threads - 1);
        printf("Number of spelling errors: %d\n", global_mistakes.total_mistake_count);

        if (global_mistakes.unique_count == 0) {
            printf("No misspellings!\n");
        }
        else if (global_mistakes.unique_count == 1) {
            printf("One most common misspelling: %s (%d times)\n", global_mistakes.words[0], global_mistakes.word_counts[0]);
        }
        else if (global_mistakes.unique_count == 2) {
            printf("Two most common misspellings: %s (%d times), %s (%d times)\n", global_mistakes.words[0], global_mistakes.word_counts[0], global_mistakes.words[1], global_mistakes.word_counts[1]);
        }
        else {
            printf("Three most common misspellings: %s (%d times), %s (%d times), %s (%d times)\n", global_mistakes.words[0], global_mistakes.word_counts[0], global_mistakes.words[1], global_mistakes.word_counts[1], global_mistakes.words[2], global_mistakes.word_counts[2]);
        }
    }
    
    // Clean up remaining resources
    deinitSpellingMistakes(&global_mistakes);
    free(threads);

    pthread_mutex_lock(&file_lock);
    fclose(output_file);

    return 0;
}
