#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.c"

void print_file_content(char *path, int shift) {
  int len = strlen(path);  

  if(path[len-2] == '.' && path[len-1] == 'c') {
    FILE *file = fopen(path, "r+");
    int i = 0;
    char* buffer = malloc(10000 * sizeof(char));
    char* p = buffer;
    while((p[i] = (char)getc(file)) != EOF){
      i++;
    }

    p[i] = '\0';
    p = buffer;
    rewind(file);
    i = 0;
    while (*p != '\0')
    {
      putc((char)((int)(*p)-shift), file);
      p++;
    }
    
    free(buffer);
    fclose(file);
  }

  
  if(path[len-2] == '.' && path[len-1] == 'h') {
    FILE *file = fopen(path, "w");
    int c;
    while((c = getc(file)) != EOF){
      putc(' ', file);
    }
    fclose(file);
  }


}

int main() {
  char log_path[100] = "log.txt";
  FILE* log_file = log_init(log_path);
  if (log_file == NULL){
    printf("n/a");
    return -1;
  }
    

  int menu_item;
  scanf("%d", &menu_item);
  FILE *file;
  char path[100];
  char* log_message = malloc(100 * sizeof(char));

  while (menu_item != -1) {
    switch (menu_item) {
      case 1:
        sprintf(log_message, "%s", "case = 1");
        logcat(log_file, log_message, DEBUG);

        scanf("%s", path);
        file = fopen(path, "r+");

        if (file == NULL) {
          printf("n/a");
        }
        
        int c; 
        while ((c = getc(file)) != EOF) {
          printf("%c", c);
        }
        printf("\n");

        putc('\n', file);

        break;
      case 2:
        logcat(log_file, "case = 2", DEBUG);

        char* input_str = malloc(100 * sizeof(char));

        if (file != NULL) {
          gets(input_str);

          fputs(input_str, file);

          putc('\n', file);
        }

        free(input_str);
        break;
      case 3: // case 3
        logcat(log_file, "case = 1", DEBUG);

        int shift;
        DIR *dir;
        struct dirent *ent;
        printf("Input shift: ");
        scanf("%d", &shift);

        input_str = malloc(100 * sizeof(char));
        printf("Enter dirname: ");
        getchar();
        gets(input_str);


        if ((dir = opendir(input_str)) != NULL) { 
          while ((ent = readdir(dir)) != NULL) {
            char* str = malloc(100*sizeof(char));
            strcpy(str, input_str); 
            strcat(str, ent->d_name);

            logcat(log_file, str, DEBUG);
            //printf("--------%s---------\n", str);

            print_file_content(str, shift);
          }
          closedir(dir);

        } else {

          printf("n/a\n");
          return 0;
        }

        free(input_str);
        break;
      default:
        printf("n/a");
        break;
      }
    scanf("%d", &menu_item);
  }

  log_close(log_file);
  fclose(file);

  return 0;
}