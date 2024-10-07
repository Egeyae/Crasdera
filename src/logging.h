//
// Created by Egeyae on 07/10/24.
//

#ifndef LOGGING_H
#define LOGGING_H

typedef enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
} LogLevel;

void log(LogLevel level, char* message, int exec_level);

#endif //LOGGING_H
