#include "config.h"
#include "utils.h"



// парс строки по пробелам

std::vector<std::string> Split_String(const std::string& str) {
    std::istringstream iss(str);

    return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};
}



// число ли эта строка

bool Is_Digit(const std::string& str) {

    if (str.empty()) return false;

    for (char ch : str)
        if (!std::isdigit(ch)) return false;

    return true;
}



// рандомное число

int Random_Number(int min, int max) {

    static bool initialized = false;

    if (!initialized) {

        srand(static_cast<unsigned int>(time(0)));
        initialized = true;
    }

    return rand() % (max - min + 1) + min;
}


// рандомный символ

char Random_Char() {

    static bool initialized = false;

    if (!initialized) {
        
        srand(static_cast<unsigned int>(time(0)));
        initialized = true;
    }

    return (rand() % 2 == 0) ? 'h' : 'v';
}