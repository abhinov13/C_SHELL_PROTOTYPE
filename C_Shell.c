//LIBRARIES INCLUDED
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


int main()
{
        clear();
        print_declaration();
        print_preface();
        return 0;
}
