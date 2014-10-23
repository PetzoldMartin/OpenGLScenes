#include "console.h"

#include <iostream>

using namespace std;


void Console::WriteError(std::string text)
{
    Write("Error: " + text);
}

void Console::Write(std::string text)
{
    cout << text << endl;
}
