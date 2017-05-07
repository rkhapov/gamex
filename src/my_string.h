
#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <string>
#include <cctype>

namespace gamex
{
    std::string constructMessage(const char *format, ...);

    std::string convertToLowerCase(const std::string &str);
}

#endif // STRING_H

