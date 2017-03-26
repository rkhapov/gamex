
#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <string>
#include <cctype>

namespace gamex
{
    const int BUFFER_SIZE = 500;
    extern thread_local char buffer[BUFFER_SIZE];

    std::string constructMessage(const char *format, ...);

    std::string convertToLowerCase(const std::string &str);
}

#endif // STRING_H

