// a1_2_wordShuffling
// Dallas Hart
//
// reads all "words" from all-words.txt, puts it into lower-case, remove non-letters, remove duplicate words, make arrays of all remaing words according to the length of the word

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Cleans the string of unwanted characters
std::string cleanString(std::string word) {
    std::string result;
    std::for_each(word.begin(), word.end(), [&result](unsigned char c) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            result += std::tolower(c);
        }
    });
    return result;
}

int main() {
    std::ifstream file("all-words.txt");
    
    if (file.is_open()) {
        std::string line;
        std::vector<std::string> fileData;

        // Read the file and clean the strings
        while (getline(file, line)) {
            std::string clean = cleanString(line);
            if (clean.length() > 0)
                fileData.push_back(clean);
        }

        // Sort alphabetically to remove dupes
        std::sort(fileData.begin(), fileData.end());

        // Store in a map as we don't know what the lengths are.
        std::unordered_map<std::size_t, std::size_t> lengthCount;
        lengthCount[fileData[0].length()]++;
        for (std::size_t i = 1; i < fileData.size(); i++) {
            // Compare against previous word for duplicates
            if (fileData[i] != fileData[i - 1]) {
                lengthCount[fileData[i].length()]++;
            }
        }

        // Output results
        for (auto& data : lengthCount) {
            std::cout << "There are/is " << data.second << " word(s) with a length of " << data.first << std::endl;
        }
        file.close();
    } else {
        std::cout << "Could not open file!";
    }
    return 0;
}

/*
******s-iMac:assignment code ******$ ./out
There are/is 1 word(s) with a length of 45
There are/is 3 word(s) with a length of 27
There are/is 11 word(s) with a length of 24
There are/is 1 word(s) with a length of 31
There are/is 2 word(s) with a length of 29
There are/is 2 word(s) with a length of 28
There are/is 7 word(s) with a length of 25
There are/is 35 word(s) with a length of 23
There are/is 88 word(s) with a length of 22
There are/is 196 word(s) with a length of 21
There are/is 1738 word(s) with a length of 18
There are/is 3505 word(s) with a length of 17
There are/is 890 word(s) with a length of 19
There are/is 424 word(s) with a length of 20
There are/is 10692 word(s) with a length of 15
There are/is 6173 word(s) with a length of 16
There are/is 25937 word(s) with a length of 13
There are/is 17407 word(s) with a length of 14
There are/is 35931 word(s) with a length of 12
There are/is 45764 word(s) with a length of 11
There are/is 54374 word(s) with a length of 10
There are/is 61613 word(s) with a length of 9
There are/is 61121 word(s) with a length of 8
There are/is 52108 word(s) with a length of 7
There are/is 22466 word(s) with a length of 5
There are/is 10655 word(s) with a length of 4
There are/is 4408 word(s) with a length of 3
There are/is 567 word(s) with a length of 2
There are/is 39104 word(s) with a length of 6
There are/is 26 word(s) with a length of 1
*/