/// Fully working text-based hangman
/// (c) Ervin Ungureanu 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

string randomWord();

int main()
{
    srand (time(NULL));
    string word = randomWord();
    cout << word;
    vector <string> guessedLetters; /// tracks which letters are guessed
    string input;
    int wrongGuess = 0; /// tracks how many wrong guesses are made
    int correctGuess = 0;
    bool gameEnd = false;
    bool letterFound = false;

    while (!gameEnd) ///driver code
    {
        cout << "Enter a letter to guess" << endl;
        cin >> input;
        if (input == word || correctGuess == word.length())
        {
            gameEnd = true;
            cout << "you are correct" << endl; /// if they input the whole word, then end the program (if correct)
            return 1;
        }
        else if (input.length() > 1) /// if they're not inputting the word then it should only be a letter
        {
            cout << "INVALID" << endl;
            return -1;
        }
        system("cls"); ///clears screen
        guessedLetters.push_back(input);
        ///printing the puzzle (word = w__d)
        for (int counter = 0; counter < word.length(); counter++)
        {
            for (int i = 0; i < guessedLetters.size(); i++)
            {
                if (guessedLetters[i].at(0) == word.at(counter))
                {
                    cout << guessedLetters[i]; ///cout the letter that is found
                    letterFound = true; ///note that there has been a letter 
                    if (counter == word.length() - 1)
                    {
                        cout << endl; /// if at end of word, new line
                    }
                    break; ///skip the rest of the loop, not needed 
                }   
            }
            if (letterFound == true)
            {
                letterFound = false;
                correctGuess++;
                continue;
            }
            else if (letterFound == false)
            {
                cout << "_"; /// will cout a blank by default
                if (counter == word.length() - 1)
                {
                    cout << endl; /// if at end of word, new line
                }
                continue;
            }
        }
        if (letterFound == false) ///
        {
            wrongGuess++;
            cout << wrongGuess << " wrong guesses" << endl;
        }
        letterFound = false;
        if (wrongGuess == 6) /// 7 wrong guesses and you're out
        {
            gameEnd = true;
            cout << "you lost, the word was " << word << endl;
        }
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

/*
stickman looks like:
  O
 /|\
 / \
*/