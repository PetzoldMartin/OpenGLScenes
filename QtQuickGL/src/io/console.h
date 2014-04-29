#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

class Console
{
public:
    static void WriteError(std::string text);
    static void Write(std::string text);
};

#endif // CONSOLE_H
