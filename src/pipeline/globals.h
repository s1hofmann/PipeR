#pragma once

#include <iostream>

/**
  *
  * Global pipeline settings
  *
  */

//FIXME Handle this via cmake options
#define USE_TBB 1

#if USE_TBB
#include <tbb/parallel_for.h>
#endif


/**
  * Variadic template functions for debug / warning / log output
  */

//Template method for output of a single argument
template<typename T>
void write(T value) {
    std::cout << value << std::endl;
}


//Template method for output of n arguments
template<typename T, typename... O>
void write(T arg, O... other) {
    std::cout << arg << " ";
    write(other...);
}


template <typename... T>
void debug(T... args) {
    std::cout << "DEBUG: ";
    //Start recursion
    write(args...);
}


template <typename... T>
void info(T... args) {
    std::cout << "INFO: ";
    write(args...);
}


template <typename... T>
void warning(T... args) {
    std::cout << "WARNING: ";
    write(args...);
}


template <typename... T>
void error(T... args) {
    std::cout << "ERROR: ";
    write(args...);
}
