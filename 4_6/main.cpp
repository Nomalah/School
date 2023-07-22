#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cctype>

//using namespace std;

template<typename First, typename ... T>
bool isEqualTo(First &&first, T && ... t){
    return ((first == t) || ...);
}

std::string cleanString(std::string toClean){
    for(size_t pos = toClean.length() - 1; pos != 0; pos--){
        toClean[pos] = std::tolower(toClean[pos]);
        if(isEqualTo(toClean[pos], '.', '!', '?', ';', ':', ',', '\'', '\"', '-'))
            toClean.erase(pos, 1);
    }
    //std::transform(toClean.begin(), toClean.end(), toClean.begin(), [](unsigned char c){return std::tolower(c);});
    return toClean;
}
 
int main(){
    std::ifstream inputFile("romeo_julliet.txt", std::ios_base::in);
    if(!inputFile.is_open()){
        std::cerr << "Could not open file!" << std::endl;
        return -1;
    }

    std::unordered_map<std::string, size_t> words;

    while(!inputFile.eof()){
        std::string temp;
        inputFile >> temp;
        temp = cleanString(temp);
        if(words.find(temp) == words.end())
           words[temp] = 0; 
        words[temp]++;
    }

    for(auto i : words)
        std::cout << std::setw(15) << i.first << " |" << std::setw(10) << i.second << std::endl;

    return 0;
}