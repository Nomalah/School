#include <iostream>
#include <string>

template <class T>
bool isConvertableTo(std::string input) {
    return false;
}

template <>
bool isConvertableTo<int>(std::string input) {
    try {
        std::stoi(input);
    } catch (...) {
        return false;
    }
    return true;
}

template <>
bool isConvertableTo<long long>(std::string input) {
    try {
        std::stoll(input);
    } catch (...) {
        return false;
    }
    return true;
}

template <>
bool isConvertableTo<unsigned long>(std::string input) {
    try {
        std::stoul(input);
    } catch (...) {
        return false;
    }
    return true;
}

template <>
bool isConvertableTo<float>(std::string input) {
    try {
        std::stof(input);
    } catch (...) {
        return false;
    }
    return true;
}

template <class T>
T convertTo(std::string input) {
    return NULL;
}

template <>
int convertTo<int>(std::string input) {
    return std::stoi(input);
}

template <>
long long convertTo<long long>(std::string input) {
    return std::stoll(input);
}

template <>
unsigned long long convertTo<unsigned long long>(std::string input) {
    return std::stoull(input);
}

template <>
unsigned long convertTo<unsigned long>(std::string input) {
    return std::stoul(input);
}

template <>
float convertTo<float>(std::string input) {
    return std::stof(input);
}

template <class T>
T input(std::string message){
    std::string input;
    do {
        std::cout << message;
        std::cin >> input;
    } while (!isConvertableTo<T>(input));
    return convertTo<T>(input);
}
