/// Fully working text-based hangman
/// (c) Ervin Ungureanu 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

string randomWord();

int main(){
    srand (time(NULL));
    string word = randomWord();
    vector <char> correctLetters; /// tracks which letters are guessed
    string currentGuess; // The current guess can either be a word or a letter
    int wrongGuess = 0; /// tracks how many wrong guesses are made

    // Game loop
    while (true){
        cout << "Enter a letter or the whole word to guess:" << endl;
        cin >> currentGuess;

        // If they guess the word straight up
        if (currentGuess == word){
            cout << "You guessed the word, Congrats!" << endl; /// if they input the whole word, then end the program (if correct)
            break;

        // If they guess a word, but it's wrong
        }else if (currentGuess.length() > 1){
            cout << "Your guess was wrong!" << endl;
            wrongGuess++;
        
        // If they guess a letter
        }else{
            // If the letter is in the word, add it to the guessedLetters
            if(word.find(currentGuess[0]) != string::npos)
                correctLetters.push_back(currentGuess[0]);

            // Otherwise, it's a wrong guess
            else
                wrongGuess++;
        }

        system("clear"); ///clears screen
        
        // Set the output word to the same length as the word
        string outputWord = word;

        // Fill the output word with underscores.
        for(char& c : outputWord)
            c = '_';

        // printing the puzzle (word = w__d)
        // Check for each letter of the original word, to see if it matches
        for (int i = 0; i < word.length(); i++) 
            // Check against all correct letters
            for(int j = 0; j < correctLetters.size(); j++)
                // If the correct letter is equal to the word's letter
                if(word[i] == correctLetters[j]){
                    outputWord[i] = word[i]; // Reveal a letter
                    break; // Break for efficency
                }

        // output the output word
        cout << outputWord << endl;
        
        if (wrongGuess == 7) /// 7 wrong guesses and you're out
        {
            cout << "you lost, the word was " << word << endl;
            break;
        }
        cout << 7 - wrongGuess << " wrong guesses left!" << endl;
    }
    return 0; /// end after loop is done
}

string randomWord()
{
    vector <string> allWords;
    string temp;
    ifstream words("hangman.txt"); ///getting random word
    while (!words.eof())
    {
        words >> temp;
        allWords.push_back(temp);
    }
    return allWords[(rand() % allWords.size())];
}