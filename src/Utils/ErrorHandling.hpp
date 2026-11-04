#pragma once

#include <exception>
#include <string>

class NanoException : public std::exception {
public:
    NanoException(const std::string &msg) : _msg(msg) {}
    const char *what() const noexcept override { return _msg.c_str(); }

private:
    std::string _msg;
};
