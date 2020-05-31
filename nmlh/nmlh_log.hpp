#pragma once

#define ERROR_MESSAGES 1

#if ERROR_MESSAGES == 1
    #include <iostream>
    #define LOG_ERR(message, data, err_lvl)                             \
    {                                                                   \
        std::string __clr;                                              \
        switch(err_lvl){                                                \
            case 1: __clr = "\033[38;5;9m [Fatal]\n\t"; break;          \
            case 2: __clr = "\033[38;5;11m [Error]\n\t"; break;         \
            case 3: __clr = "\033[38;5;10m [Warning]\n\t"; break;       \
            default: __clr = "\033[38;5;14m [Notif]\n\t"; break;        \
        }                                                               \
        std::cerr << __clr << message << data << "\033[38;5;15m\n";     \
    }
#else
    #define LOG_ERR(message, data, err_lvl)
#endif