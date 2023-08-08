
#if !defined LOGGER_H_GUARD
#define LOGGER_H_GUARD

/** available logger levels */
#define LOG_CRITICAL 1
#define LOG_ERROR    2
#define LOG_WARN     3
#define LOG_INFO     4
#define LOG_DEBUG    5
#define LOG_VERBOSE  6
#define LOG_SPAM     7

#if (!defined LOGGER_ENABLED)
    #warning "macro LOGGER_ENABLED shall be defined before include"
#endif

#if (!defined LOGGER_LEVEL) || (LOGGER_LEVEL == 0)
    #warning "Please define LOGGER_LEVEL before include"
    #define LOGGER_LEVEL LOG_INFO
#endif

//TODO implement logger_channels (redefinition of Serial.print may be needed)
#if (defined LOGGER_ENABLED) && (LOGGER_ENABLED != 0)
    #define LOGGER(LVL, ...) do{ if((LVL)<=(LOGGER_LEVEL)) { Serial.print(__VA_ARGS__); } }while(0)
    #define LOGGERLN(LVL, ...) do{ if((LVL)<=(LOGGER_LEVEL)) { Serial.println(__VA_ARGS__); } }while(0)
#else
    #define LOGGER(LVL, ...)
    #define LOGGERLN(LVL, ...)
#endif

#else
#error LOGGER REDEFINED!
#endif

