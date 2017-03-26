#include <cstdio>
#include <cstdarg>

#include "my_string.h"

thread_local char gamex::buffer[gamex::BUFFER_SIZE];

std::string gamex::constructMessage(const char *format, ...)
{
    std::va_list list;
    va_start(list, format);

    std::vsprintf(buffer, format, list);

    va_end(list);

    return buffer;
}


std::string gamex::convertToLowerCase(const std::string &str)
{
    int i = 0;

    for (; i < static_cast<int>(str.size()); i++)
        buffer[i] = std::tolower(str[i]);

    buffer[i] = '\0';

    return buffer;
}
