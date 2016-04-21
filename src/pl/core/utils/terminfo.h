#pragma once

#include <cstdio>
#include <sys/ioctl.h>
#include <unistd.h>

class TermInfo
{
public:
    TermInfo();
    void update();

    int getLines() const;
    int getCols() const;

private:
    winsize winSize;
    int lines;
    int cols;
};
