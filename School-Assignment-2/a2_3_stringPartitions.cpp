// a2_3_stringPartitions
// Dallas Hart
//
// Cleans words from "all-words.txt" and uses them as a dictionary to find all string partitions of an input

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

// Cleans the string of unwanted characters
std::string cleanString(std::string word)
{
    std::string result;
    std::for_each(word.begin(), word.end(), [&result](unsigned char c) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            result += std::tolower(c);
        }
    });
    return result;
}

int recursive(const std::string &sentence, std::size_t insert, std::size_t insertSize, const std::unordered_map<std::string, bool> &dictionary, std::vector<std::string> result, int depth)
{
    // Total solutions to the problem
    static int total = 0;

    // Check the dictionary to see if the selection is a "word"
    if (dictionary.find(sentence.substr(insert, insertSize)) != dictionary.end())
    {
        result.push_back(sentence.substr(insert, insertSize));
        insert += insertSize; // Move the insert selector farther into the sentence
        // If the insert selector made it to the end of the sentence, it's a solution
        if (insert == sentence.length())
        {
            total++;
            for (auto &w : result)
            {
                std::cout << w << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            // Recurse for all possible next words
            for (std::size_t i = 1; i <= sentence.length() - insert; i++)
            {
                recursive(sentence, insert, i, dictionary, result, depth + 1);
            }
        }
    }
    return total;
}

int main()
{
    // File being used.
    std::ifstream file("all-words.txt");

    if (file.is_open())
    {
        std::string line;
        std::unordered_map<std::string, bool> dictionary;

        // Read the file and clean the strings
        while (getline(file, line))
        {
            std::string clean = cleanString(line);
            if (clean.length() > 0)
            {
                dictionary[clean] = true;
                //std::cout << clean << std::endl;å
            }
        }
        file.close();

        std::string inputString;
        std::cout << "Enter a string to see it's partitions: ";
        std::cin >> inputString;
        inputString = cleanString(inputString);

        int solutions = 0;

        // Must run the function for all possible starting words
        for (int i = 0; i <= inputString.length(); i++)
        {
            solutions = recursive(inputString, 0, i, dictionary, {}, 0);
        }
        std::cout << "There are " << solutions << " solutions!" << std::endl;
    }
    else
    {
        std::cout << "Could not open file!";
    }
    return 0;
}

/*
******s-iMac:assignment code ******$ ./out
Enter a string to see it's partitions: hello
h e l l o 
h e l lo 
h e ll o 
h e llo 
h el l o 
h el lo 
h ell o 
he l l o 
he l lo 
he ll o 
he llo 
hel l o 
hel lo 
hell o 
hello 
There are 15 solutions!
******s-iMac:assignment code ******$ ./out
Enter a string to see it's partitions: bruh
b r u h 
b r uh 
b ru h 
br u h 
br uh 
There are 5 solutions!
******s-iMac:assignment code ******$ ./out
Enter a string to see it's partitions: BOTHEARTHANDSATURNSPIN
...
bothe artha nd saturn spin 
There are 533280 solutions!
*/