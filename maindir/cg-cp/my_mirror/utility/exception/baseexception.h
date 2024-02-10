#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

class BaseException: public std::exception
{
protected:
    char _msg[512];
public:
    BaseException(std::string file, size_t line)
    {
        auto error_time = std::time(nullptr);
        auto tm = *std::localtime(&error_time);
        std::ostringstream ss;
        ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        ss.imbue(std::locale("ru_RU.utf-8"));

        snprintf(_msg, sizeof(_msg), "filename: %.*s\nline: %zu\ntime: %.*s\ninfo: ",
                 (int) file.size(), file.data(),
                 line,
                 (int) ss.str().size() , ss.str().data());
    }

    virtual ~BaseException() {};

    virtual const char *what() const noexcept override
    {
        return _msg;
    };
};


#endif // BASEEXCEPTION_H
