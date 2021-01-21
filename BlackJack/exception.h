#ifndef EXEPTION_H
#define EXEPTION_H
#include <exception>
#include <iostream>

class StrSettingError : public std::exception {
public:
	int what() {
		std::cout << "Some strategy is unable to continue the game due to a configuration file access error." << std::endl;
		std::cout << "Game will be terminated.." << std::endl;
		return 0;
	}
};

class BadInput : public std::exception {
public:
    int what() {
        std::cout << "Bad input" << std::endl;
        return 1;
    }
};

class BadStr : public std::exception {
public:
    int what() {
        std::cerr << " Too few strategies identified, impossible to continue the game" << std::endl;
        return 0;
    }
};

#endif