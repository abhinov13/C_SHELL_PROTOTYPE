//LIBRARIES INCLUDED
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<readlines/readlines.h>
#include<readlines/history.h>

//MAX-SIZE DEFINITIONS
#define BUFFERSIZE 1000
#define MAXLIST 100

//CONSTANT DECLARATIONS
const char* declaration = "THE SHELL HAS STARTED";

//FUNCTIONS
void print_declaration()
{
        printf("%s\n",declaration);
}
void print_preface()
{
        char directory_Address[BUFFERSIZE];
        getcwd(directory_Address,BUFFERSIZE);
        printf("%s:%s~$\n",getenv("USER"),directory_Address);
}
void clear()
{
        printf("\033[H\033[J");
}
void Help()
{
	puts("\nThe World of Linux command Shell Interpreter Welcome You, Lets Enjoy the Help"
		"\n List of the some of the command you find in the shell are listed: -------"
		"\n cd "
		"\n ls"
		"\n clear"
		"\n .............More on:");
	return;
}

int main()
{
        clear();
        print_declaration();
        print_preface();
        Help();
        return 0;
}
