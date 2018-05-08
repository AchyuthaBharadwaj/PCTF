#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

unsigned int num_files;
char name[100];
char password[100];

struct temp_files {
   char* contents;
   unsigned int size;
   struct temp_files* next;
};

struct temp_files* head = NULL;

int readline(char *buf, int size) {
  int i;
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
  return size-1;
}

void read_in_bytes(char* new_file, unsigned int the_size)
{
   int i = 0;
   while (i < the_size)
   {
	  if (read(0, new_file+i, 1) != 1)
	  {
		 exit(0);
	  }
	  i += 1;
   }
}

void printmenu()
{
   printf("Hello, welcome to the secure data storage system.\n");
   printf("(1) Securely start backup.\n");
   printf("(2) Retrieve secure backup.\n");
   printf("(3) Exit.\n");
   printf("> ");
   fflush(stdout);
}

void print_backup_menu()
{
   printf("You currently have %d files ready to be stored for backup.\n", num_files);
   printf("(1) Add a file.\n");
   printf("(2) Remove all files.\n");
   printf("(3) Store files.\n");
   printf("(4) Return to menu without saving.\n");
   fflush(stdout);	  
}

void add_file()
{
   char size[20];
   unsigned int the_size;
   char* new_file;
   struct temp_files* tmp;
   printf("How big (in bytes) is your file? ");
   fflush(stdout);   
   readline(size, 20);

   the_size = atoi(size);
   new_file = malloc(the_size);
   
   printf("Go ahead, send your file\n");
   fflush(stdout);

   read_in_bytes(new_file, the_size);

   if (head == NULL)
   {
	  head = (struct temp_files*) malloc(sizeof(struct temp_files));
	  head->contents = NULL;
	  head->next = NULL;
   }
   tmp = head;
   while (tmp->next != NULL)
   {
	  tmp = tmp->next;
   }

   tmp->next = (struct temp_files*) malloc(sizeof(struct temp_files));
   tmp->next->next = NULL;
   tmp->next->contents = new_file;
   tmp->next->size = the_size;

   num_files += 1;

   printf("File successfully added.\n");
   fflush(stdout);
}


void free_list(struct temp_files* cur)
{
   if (cur == NULL)
   {
	  return;
   }
   if (cur->next != NULL)
   {
	  free_list(cur->next);
   }

   if (cur->contents != NULL)
   {
	  free(cur->contents);
   }
   free(cur);
}

void remove_all_files()
{
   free_list(head);

   head = NULL;
   num_files = 0;
}

void store_all_files()
{
   char filename[120];
   FILE* new_file;
   struct temp_files* tmp;

   strcat(filename, name);
   strcat(filename, "_");
   strcat(filename, password);
   strcat(filename, ".secure.bak");

   if (head == NULL)
   {
	  printf("ERROR, no files to store.\n");
	  fflush(stdout);
	  return;
   }

   new_file = fopen(filename, "w+");

   tmp = head->next;
   while(tmp != NULL)
   {
	  fwrite(tmp->contents, tmp->size, 1, new_file);
	  tmp = tmp->next;
   }

   fclose(new_file);

   remove_all_files();
}

void get_info()
{
   // TODO: sanity check name and password
   printf("Select a name for your backup: ");
   fflush(stdout);
   readline(name, 99);
   name[100]='\0';
   int a= strlen(name);
   int i;
   for (i=0;i<a;i++)
   {
	if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9'))
	{
		//printf("\n");
	}
	else{
	     printf("Goodbye!\n");
             fflush(stdout);
	     exit(0);
	}
   }
   printf("\n");
   
   printf("Choose a secure password for your backup: ");
   fflush(stdout);
   readline(password, 100);
   int b= strlen(password);
   int j;
   for (j=0;j<b;j++)
   {
       if((password[j] >= 'a' && password[j] <= 'z') || (password[j] >= 'A' && password[j] <= 'Z') || (password[j] >= '0' && password[j] <= '9'))
       {
   //                     printf("\n");
       }
       else{
	    printf("Goodbye!\n");
            fflush(stdout);
            exit(0);
	}
   }
   printf("\n");
}

void start_backup()
{
   char input[40];
   num_files = 0;
   head = NULL;
   get_info();
   
   while (1)
   {
	  print_backup_menu();
	  readline(input, 40);
	  if (!strcmp(input, "1"))
	  {
		 add_file();
	  }
	  else if (!strcmp(input, "2"))
	  {
		 remove_all_files();
	  }
	  else if (!strcmp(input, "3"))
	  {
		 store_all_files();
		 break;
	  }
	  else
	  {
		 break;
	  }
   }
}

void retrieve_backup()
{
   char cmd[200];
   get_info();

   printf("Here is your backup data that was stored securely:\n");
   fflush(stdout);
   snprintf(cmd, 200, "cat %s_%s.secure.bak", name, password);
   system(cmd);
}

int main(int argc, char** argv)
{
   char input[40];
   chdir("../append/");
   while (1)
   {
	  printmenu();
	  readline(input, 40);
	  if (!strcmp(input, "1"))
	  {
		 start_backup();
	  }
	  else if (!strcmp(input, "2"))
	  {
		 retrieve_backup();
	  }
	  else
	  {
		 printf("Goodbye!\n");
		 fflush(stdout);
		 exit(0);
	  }
   }
   
}
