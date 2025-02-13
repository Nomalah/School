/// assign_3_8_cipher.cpp
/// Dallas Hart
/// 11/25/2019
/// This program will encrypt and decrypt a string
#include <iostream>
#include <string>

using namespace std;

int intIn(string inMessage, string failMessage);
string in(string inMessage, string failMessage);
void encrypt(string word, int shift);
void decrypt(string word, int shift);

int main()
{
    /// encrypt
    cout << "encrypt" << endl;
    /// input
    string inWord=in("enter a string","enter a string");
    int shiftNum=intIn("enter the shift","enter the shift");

    /// uppercase stuff
    for (int i=0; i<inWord.length(); i++)
    {
        inWord.at(i)=toupper(inWord.at(i));
    }
    encrypt(inWord,shiftNum); /// function
    ///delay
    for (int i=0; i<10; i++)
    {
        for (int i=0; i<10000000; i++)
        {
            int x=2*i;
        }
    }
    cout << endl << "decrypt" << endl;
    /// input
     string encryptedWord=in("enter the encrypted string","enter a string");
    shiftNum=intIn("enter the decrypt shift","enter the decrypt shift");
    /// uppercase stuff
    for (int i=0; i<encryptedWord.length(); i++)
    {
        encryptedWord.at(i)=toupper(encryptedWord.at(i));
    }
    decrypt(encryptedWord, shiftNum);///function
    return 0;
}

string in(string inMessage, string failMessage)
{
    string input;
    cout << inMessage << endl;
    while(true)
    {
        cin >> input; // input for number of
        if (cin.fail())// dummy-proofing
        {
            cout << failMessage << endl;
            cin.clear(); //clear stream
            cin.ignore(256, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            return input; //exit the loop if everything is ok
        }
    }
}

int intIn(string inMessage, string failMessage)
{
    int input;
    cout << inMessage << endl;
    while(true)
    {
        cin >> input; // input for number of
        if (cin.fail())// dummy-proofing
        {
            cout << failMessage << endl;
            cin.clear(); //clear stream
            cin.ignore(256, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            return input; //exit the loop if everything is ok
        }
    }
}

void encrypt(string word, int shift)
{
    int wordNum [word.length()];
    for(int i=0; i<word.length(); i++)
    {
        wordNum [i] = word.at(i);
        if(wordNum [i] >= 65 && wordNum [i] <= 90) /// only change if valid cipher character
        {
            wordNum [i]+=shift;
            if (wordNum[i] > 90)///loop if over
            {
                wordNum[i]-=26;///loop
            }
        }
        if(wordNum [i] >= 48 && wordNum [i] <= 57)/// only change if valid cipher character
        {
            wordNum [i]+=shift;
            if (wordNum[i] > 57)///loop if over
            {
                wordNum[i]-=10;///loop
            }
        }
        word.at(i) = wordNum [i];
        cout << word.at(i);
    }
}

void decrypt(string word, int shift)
{
    int wordNum [word.length()];
    for(int i=0; i<word.length(); i++)
    {
        wordNum [i] = word.at(i);
        if(wordNum [i] >= 65 && wordNum [i] <= 90)/// only change if valid cipher character
        {
            wordNum [i]-=shift;
            if (wordNum[i] < 65)///loop if over
            {
                wordNum[i]+=26;///loop
            }
        }
        if(wordNum [i] >= 48 && wordNum [i] <= 57)/// only change if valid cipher character
        {
            wordNum [i]-=shift;
            if (wordNum[i] < 48)///loop if over
            {
                wordNum[i]+=10;///loop
            }
        }
        word.at(i) = wordNum [i];
        cout << word.at(i);
    }
}
/*
test cases

encrypt
enter a string
hello
enter the shift
5
MJQQT
decrypt
enter the encrypted string
mjqqt
enter the decrypt shift
5
HELLO
Process returned 0 (0x0)   execution time : 26.978 s
Press any key to continue.

*/
