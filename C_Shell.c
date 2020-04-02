//LIBRARIES INCLUDED
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//MAX-SIZE DEFINITIONS
#define MAX_PATH_SIZE 1000
#define MAX_USERNAME_SIZE 100
#define COMMAND_LIST_SIZE 50

//CONSTANT DECLARATION
const char* declaration = "THE SHELL HAS STARTED";

//FUNCTIONS
void print_declaration()
{
        printf("%s\n",declaration);
}
void get_Path(char *path)
{
        getcwd(path,MAX_PATH_SIZE);
}
void get_User_Name(char *username)
{
        username = getenv("USER");
}
void print_preface()
{
        char username[MAX_USERNAME_SIZE];
        char path[MAX_PATH_SIZE];
        get_User_Name(username);
        get_Path(path);
        printf("%s:%s~$\n",username,path);
}
void execute_command(char *args[])
{
        pid_t p1 = fork();
        if(p1 != 0)
        {
                wait(NULL);
        }
        else
        {
                execvp(args[0],args);
        }
}
void show_Command_List()
{
        printf("The supported commands are as following:\n");
        ssize_t file = open("command_list.txt",O_RDONLY);
        char file_Data[COMMAND_LIST_SIZE];
        read(file,file_Data,COMMAND_LIST_SIZE);
        printf("%s\n",file_Data);
}

int main()
{
        char *args[] = {"./clear.out",NULL};
        execute_command(args);
        print_declaration();
        print_preface();
        show_Command_List();
        return 0;
}
