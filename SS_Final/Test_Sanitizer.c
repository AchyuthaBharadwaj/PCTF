#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int isValidInput_written_by_Cha0$(char input[]) {
   int i;
   for(i = 0; i < strlen(input); i++) {
      if(!isalnum(input[i]))
         return 0;
   }
   return 1;
}

int readline_written_by_Cha0$(char *buf, int size) {
  int i;
  char *filename = "a.c";
  for(i = 0; i < size; i++) {
    if(read(0, buf+i, 1) <= 0) {
      exit(1);
    }
    if (buf[i] == '\n') {
      buf[i] = '\x00';
      return i;
    }
  }
  buf[size-1] = '\x00';

  /* time of attack */
  time_t current_time;
  char* c_time_string;
  current_time = time(NULL);
  c_time_string = ctime(&current_time); 

  FILE *fp = fopen("c_log.txt", "a");
  fprintf(fp, "\nAttack recieved: %s: { %s%s }\n\n", filename, c_time_string, buf);
  fclose(fp);

  if(isValidInput_written_by_Cha0$(buf)==0) {
     printf("Invalid Input");
     exit(1);
  }
  
  return size-1;
}

int main(){
   char a[10];
   readline_written_by_Cha0$(a, 10);
   printf("success: %s", a);
   return 0;
}
