#ifndef DATAEXCEPTION_H
#define DATAEXCEPTION_H


class DataException : public std::runtime_error
{
public:
    DataException();
};

#endif // DATAEXCEPTION_H