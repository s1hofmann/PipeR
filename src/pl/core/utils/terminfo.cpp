#include "terminfo.h"

TermInfo::TermInfo()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &this->winSize);

    this->lines = this->winSize.ws_row;
    this->cols = this->winSize.ws_col;
}

void TermInfo::update()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &this->winSize);

    this->lines = this->winSize.ws_row;
    this->cols = this->winSize.ws_col;
}

int32_t TermInfo::getLines() const
{
    return this->lines;
}

int32_t TermInfo::getCols() const
{
    return this->cols;
}

