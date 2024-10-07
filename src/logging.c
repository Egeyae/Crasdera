//
// Created by Egeyae on 07/10/24.
//

#include "logging.h"

#include <stdio.h>


void log(LogLevel level, char* message, int exec_level) {
    char *level_str;
    switch (level) {
        case LOG_DEBUG:
            level_str = "DEBUG";
        case LOG_INFO:
            level_str = "INFO";
        case LOG_WARNING:
            level_str = "WARNING";
        case LOG_ERROR:
            level_str = "ERROR";
        default:
            level_str = "UNKNOWN";
    }
    for (int i = 0; i < exec_level; i++) {
        printf("  | ");
    }
    printf("[%s] %s \n", level_str, message);
}
