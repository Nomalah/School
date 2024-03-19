#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <math.h>

#define NUM_OF_CHARS 26


// [0] = read pipe 0, [1] = write pipe 1, [2] = read pipe 2, [3] = write pipe 2, etc.
int* pipes = NULL;
pid_t* child_pids = NULL;
int number_of_children = 0;
volatile sig_atomic_t children_active = 0;


static void child_handler(int sig) {
    // Re-assign the signal handler
    signal(SIGCHLD, child_handler);

    int status;
    pid_t pid;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Caught SIGCHLD, PID: %d, status: %d\n", pid, status);
        
        // Log what the result was of the child process
        if (WIFSIGNALED(status)) {
            printf("PID: %d was killed by %s!\n", pid, strsignal(status));
            children_active--;
            return;
        } else if (WEXITSTATUS(status) != 0) {
            printf("PID: %d had exit code: %d\n", pid, WEXITSTATUS(status));
            children_active--;
            return;
        } else {
            printf("PID: %d exited successfully!\n", pid);
        }

        int child_index = -1;
        for (int i = 0; i < number_of_children; i++) {
            if (child_pids[i] == pid) {
                child_index = i;
                break;
            }
        }

        if (child_index == -1) {
            printf("Unknown PID: %d\n", pid);
            children_active--;
            return;
        }

        // Close write side of pipe and read the letter counts from this child process
        int letter_counts[NUM_OF_CHARS] = {};
        close(pipes[child_index * 2 + 1]);
        read(pipes[child_index * 2], (void*)letter_counts, NUM_OF_CHARS * sizeof(int));

        // Generate the output file name
        int pid_length = ceil(log10(pid));
        int output_file_name_length = 4 + pid_length + 5 + 1;
        char* output_file_name = calloc(output_file_name_length, 1);
        snprintf(output_file_name, output_file_name_length, "file%d.hist", pid);

        // Open + write the histogram to the output file
        FILE* output_histogram_file = fopen(output_file_name, "w");
        if (output_histogram_file == NULL) {
            printf("Unable to open output file: \"%s\"\n", output_file_name);
            free(output_file_name);
            children_active--;
            return;
        }
        free(output_file_name);

        for (char c = 'a'; c <= 'z'; c++) {
            fprintf(output_histogram_file, "%c %d\n", c, letter_counts[c - 'a']);
        }

        fclose(output_histogram_file);
        children_active--;
    }
}

int child_process(int child_index, char* file_name) {
    sleep(1); // Give enough time for parent to kill with SIGINT

    pid_t pid = getpid();
    printf("Hello from child %d with filename: %s, in process #%d\n", child_index, file_name, pid);
    
    FILE* input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("Unable to open \"%s\"\n", file_name);
        return 1;
    }

    // Go through 
    int letter_counts[NUM_OF_CHARS] = {};
    int current_character = '\0';

    while ((current_character = fgetc(input_file)) != EOF) {
        if (current_character >= 'A' && current_character <= 'Z') {
            letter_counts[current_character - 'A']++;
        } else if (current_character >= 'a' && current_character <= 'z') {
            letter_counts[current_character - 'a']++;
        }
    }
    fclose(input_file);

    // Close the reading pipe and write the letter counts to the parent process
    close(pipes[child_index * 2]);
    write(pipes[child_index * 2 + 1], (void*)letter_counts, NUM_OF_CHARS * sizeof(int));
    
    // Wait for 10s + i * 3 to avoid race conditions
    sleep(10 + child_index * 3);
    printf("Process %d terminating...\n", pid);
    return 0;
}


int main(int argc, char* argv[]) {
    signal(SIGCHLD, child_handler);

    number_of_children = argc - 1;
    child_pids = malloc((argc - 1) * sizeof(pid_t));
    pipes = malloc((argc - 1) * 2 * sizeof(int));

    for (int i = 1; i < argc; i++) {
        printf("forking...\n");
        if (pipe(&pipes[(i-1) * 2]) == -1) {
            printf("Failed to open pipe!");
            return -1;
        }

        int child_pid = fork();
        if (child_pid < 0) {
            printf("Failed to create helper - shutting down\n");
            return -1;
        }

        if (child_pid == 0) {
            exit(child_process(i - 1, argv[i]));
        } else {
            children_active++;
            child_pids[i - 1] = child_pid;
            // SIGINT special input
            if (strcmp(argv[i], "SIG") == 0) {
                kill(child_pid, SIGINT);
            }
        }
    }

    while(children_active != 0) {
        sleep(1);
    }

    free(child_pids);
    free(pipes);

    return 0;
}
