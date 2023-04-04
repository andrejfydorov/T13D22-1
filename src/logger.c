#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"
#include <stdio.h>


FILE* log_init(char* filename){
    FILE* file = fopen(filename, "a+");
    return file;
}

int logcat(FILE* log_file, char *message, log_level level){
    if(log_file != NULL){
        time_t _time = time(NULL);
        
        struct tm *now = localtime(&_time);
        char* new_message = calloc((strlen(message) + 13), sizeof(char));
        
        char* log_str = calloc(7, sizeof(char));
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

        char str[13];
        strcat(new_message, log_str);
        strcat(new_message, " ");
        sprintf(str, "%04d", now->tm_year + 1900);
        strcat(new_message, str);
        strcat(new_message, "-");
        sprintf(str, "%02d", now->tm_mon + 1);
        strcat(new_message, str);
        strcat(new_message, "-");
        sprintf(str, "%02d", now->tm_mday);
        strcat(new_message, str);
        strcat(new_message, " ");
        sprintf(str, "%02d", now->tm_hour);
        strcat(new_message, str);
        strcat(new_message, ":");
        sprintf(str, "%02d", now->tm_min);
        strcat(new_message, str);
        strcat(new_message, ":");
        sprintf(str, "%02d", now->tm_sec);
        strcat(new_message, str);
        strcat(new_message, " ");
        strcat(new_message, message);
        strcat(new_message, "\n");

        printf("%s\n", new_message);
        //fwrite(new_message, sizeof(char), strlen(new_message), log_file);
        fputs(new_message, log_file);
        fflush(log_file);

        // free(new_message);
        // free(log_str);
        //fclose(log_file);
 
        return 1;
    }

    return 0;

}

int log_close(FILE* log_file){
    if(log_file != NULL)
        return fclose(log_file);
    else
        return -1;
}