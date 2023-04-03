#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"


FILE* log_init(char *filename){
    FILE* file = fopen(filename, "a+");
    printf("%s\n", filename);
    return file;

}

int logcat(FILE* log_file, char *message, log_level level){
    if(log_file != NULL){
        time_t _time = time(NULL);
        
        struct tm *now = localtime(&_time);
        char* new_message = malloc((strlen(message) + 14) * sizeof(char));
        
        char* log_str = malloc(10 * sizeof(char));
        switch (level)
        {
        case DEBUG:
            log_str = "DEBUG";
            break;
        case INFO:
            log_str = "INFO";
            break;
        case WARNING:
            log_str = "WARNING";
            break;
        case ERROR:
            log_str = "ERROR";
            break;
        default:
            log_str = "DEFAULT";
            break;
        }
        
        char str[10];
        strcat(new_message, log_str);
        strcat(new_message, " ");
        sprintf(str, "%4d", now->tm_year);
        strcat(new_message, str);
        strcat(new_message, "-");
        sprintf(str, "%2d", now->tm_mon);
        strcat(new_message, str);
        strcat(new_message, "-");
        sprintf(str, "%2d", now->tm_mday);
        strcat(new_message, str);
        strcat(new_message, " ");
        sprintf(str, "%2d", now->tm_hour);
        strcat(new_message, str);
        strcat(new_message, ":");
        sprintf(str, "%2d", now->tm_min);
        strcat(new_message, str);
        strcat(new_message, ":");
        sprintf(str, "%2d", now->tm_sec);
        strcat(new_message, str);
        strcat(new_message, " ");
        strcat(new_message, message);

        printf("%s", new_message);
        fwrite(new_message, sizeof(char), strlen(new_message), log_file);

        free(new_message);
        free(log_str);
        return 1;
    }
    else
        return -1;
}

int log_close(FILE* log_file){
    if(log_file != NULL)
        return fclose(log_file);
    else
        return -1;
}