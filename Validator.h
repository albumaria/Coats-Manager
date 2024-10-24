#pragma once
#include "TrenchCoat.h"
#include <string>
#include <exception>

class Validator
{
public:
	int validateTrench(TrenchCoat t);
	int validateSize(std::string size);
    int validateStringData(std::string price, std::string quantity);
};


class ValidationException : public std::exception {
private:
    std::string message;

public:
    ValidationException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
