#ifndef SPOOKYOUT_HPP
#define SPOOKYOUT_HPP

#include <iostream>
#include <string>
#include <windows.h>

class SpookyOutput
{
public:
    enum Allignment
    {
        RIGHT = 0,
        CENTER,
        LEFT,
        MOVING_CENTER
    };

    SpookyOutput();

    // Spooky output, parameter will always be string.
    SpookyOutput &operator<<(const std::string &str);

    // sets allignment for spooky print
    void setAllignment(Allignment allignment);

    // Delay between characters in milliseconds, lower is faster. Basically print speed.
    void setDelay(unsigned int integer);

    // Quick set functions
    void center();
    void left();
    void right();
    void movingCenter();

private:
    unsigned int Delay = 40;
    static int columns_in_console;
    static CONSOLE_SCREEN_BUFFER_INFO csbi;
    Allignment allignment = RIGHT;

    SpookyOutput(const SpookyOutput &) = delete;
    SpookyOutput(SpookyOutput &&) = delete;

} sout;

int SpookyOutput::columns_in_console;
CONSOLE_SCREEN_BUFFER_INFO SpookyOutput::csbi;

SpookyOutput::SpookyOutput()
{
    // What this part of the code does is find width of console to allign text.
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns_in_console = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    // It uses windows.h and is not gui portable.
}

SpookyOutput &SpookyOutput::operator<<(const std::string &str)
{
    int len = str.length();
    //std::cout << len;

    int space = (columns_in_console - len) / 2;
        for (int i = 0; i < space; i++)
            std::cout << ' ';
        for (int j = 0; j < len; j++)
        {
            std::cout << str[j];
            Sleep(Delay);
        }
        std::cout << std::endl;
    Sleep(800);
    return *this;
}
/* Sets output text allignment

Options are:
SpookyOutput::right,
SpookyOutput::center,
SpookyOutput::left (Is not complete yet),
SpookyOutput::MOVING_CENTER*/
void SpookyOutput::setAllignment(Allignment allignment)
{
    this->allignment = allignment;
}

// Sets delay between characters, default set at constructor is 50.
void SpookyOutput::setDelay(unsigned int delay)
{
    Delay = delay;
}

void SpookyOutput::center()
{
    this->allignment = SpookyOutput::CENTER;
}
void SpookyOutput::left() { allignment = SpookyOutput::LEFT; }
void SpookyOutput::right() { allignment = SpookyOutput::RIGHT; }
void SpookyOutput::movingCenter() { allignment = SpookyOutput::MOVING_CENTER; }
#endif


/*    if (allignment == RIGHT)
    {
        for (int i = 0; i < len; i++)
        {
            std::cout << str[i];
            Sleep(Delay);
        }
        std::cout << std::endl;
    }
    else if (allignment == MOVING_CENTER)
    {
        for (int i = 0; i < len; i++)
        {
            int space = (columns_in_console - ((i % columns_in_console) + 1)) / 2;
            for (int j = 0; j < space; j++)
                std::cout << ' ';
            std::cout << str.substr((i / columns_in_console) * columns_in_console, i % columns_in_console + 1);
            Sleep(Delay);
            if (i % (columns_in_console - 1) == 0 && i != 0)
                std::cout << std::endl;
            else if (i == len)
                ;
            else
                std::cout << '\r';
        }
        std::cout << std::endl;
    }
    else if (allignment == CENTER)
    {
        int space = (columns_in_console - len) / 2;
        for (size_t i = 0; i < space; i++)
            std::cout << ' ';
        for (size_t i = 0; i < len; i++)
        {
            std::cout << str[i];
            Sleep(Delay);
        }
        std::cout << std::endl;
    }
    else if (allignment == LEFT)
    {
        for (int i = 0; i < len; i++)
        {
        }
        std::cout << "A work in progress." << std::endl;
    }*/