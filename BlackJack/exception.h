#ifndef EXEPTION_H
#define EXEPTION_H
#include <exception>
#include <iostream>

class BadArguments : public std::exception {
public:
	int what() {
		std::cout << "Undefined strategy ID" << std::endl;
		return 0;
	}
};

class MemoryError : public std::exception {};

class StrSettingError : public std::exception {
public:
	int what() {
		std::cout << "Some strategy is unable to continue the game due to a configuration file access error." << std::endl;
		std::cout << "Game will be terminated.." << std::endl;
		return 0;
	}
};
#endif