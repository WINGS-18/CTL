#pragma once

#include <iostream>

#ifndef NDEBUG

    //debug mode

    #define CTL_ASSERT(condition, message) \
        do { \
            if(!(condition)) { \
                std::cerr << "  Condition: " << #condition << "\n" \
                          << "  Message: " << message << "\n" \
                          << "  File: " << __FILE__ << " : " << __LINE__ << "\n" \
                          << "  Function: " << __PRETTY_FUNCTION__ << "\n\n"; \
                std::abort(); \
            } \
        } while(false)

    #define CTL_PANIC(message) \
        do { \
            std::cerr << "  Message: " << message << "\n" \
                      << "  File: " << __FILE__ << " : " << __LINE__ << "\n" \
                      << "  Function: " << __PRETTY_FUNCTION__ << "\n\n"; \
            std::abort(); \
        } while(false)

#else
    
    //release mode

    #define CTL_PANIC(message)  std::abort()
    #define CTL_ASSERT(condtion, message) ((void) 0)

#endif