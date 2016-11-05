#pragma once

#include <cstdio>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdint>


class TermInfo
{
public:
    TermInfo();
    void update();

    int32_t getLines() const;
    int32_t getCols() const;

private:
    winsize winSize;
    int32_t lines;
    int32_t cols;
};
