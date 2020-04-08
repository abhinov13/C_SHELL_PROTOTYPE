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
#define MAX_COMMAND_LIST_SIZE 10
#define MAX_COMMAND_LENGTH 1000
#define MAX_COMMANDSEG_LENGTH 100
#define MAX_COMMAND_ARGS_SIZE 10

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
        printf("%s:%s~$",username,path);
}
void execute_command(char *command[])
{
        pid_t p1 = fork();
        if(p1 != 0)
        {
                wait(NULL);
        }
        else
        {
                execvp(command[0],command);
        }
}
void execute_piped_command(int input_file_descriptor,int output_buffer,char* command[])
{
        pid_t proc = fork();
        if(proc < 0)
        {
                perror("UNABLE TO FORK");
                exit(-1);
        }
        else if(proc == 0)
        {
                if(input_file_descriptor != 0)
                {
                        dup2(input_file_descriptor,0);
                        close(input_file_descriptor);
                }
                if(output_buffer != 1)
                {
                        dup2(output_buffer,1);
                        close(output_buffer);
                }
                execvp(command[0],command);
        }
        else
        {
                wait(NULL);
        }
}
void start_process(int number_of_segments,char* parsed_command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_ARGS_SIZE])
{
        int i = 0;
        int input_file_descriptor = 0;
        int pipeline[2];
        while(i+1 != number_of_segments)
        {
                printf("i is %d\n",i );
                int check_pipe = pipe(pipeline);
                if(check_pipe == -1)
                {
                        perror("ERROR CREATING PIPE\n");
                        exit(-1);
                }
                execute_piped_command(input_file_descriptor,pipeline[1],parsed_command[i]);
                close(pipeline[1]);
                input_file_descriptor = pipeline[0];
                i++;
        }
        if(input_file_descriptor != 0)
        {
                dup2(input_file_descriptor,0);
                close(input_file_descriptor);
        }
        execute_command(parsed_command[i]);
}
void show_Command_List()
{
        printf("The supported commands are as following:\n");
        ssize_t file = open("command_list.txt",O_RDONLY);
        char file_Data[MAX_COMMAND_LIST_SIZE];
        read(file,file_Data,MAX_COMMAND_LIST_SIZE);
        printf("%s\n",file_Data);
}
void seperate_piped(char* input_command,int* number_of_segments,char command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_LENGTH])
{

        *number_of_segments = 0;
        char* segment;
        while( (segment = strsep(&input_command,"|")) != NULL )
        {
                strcpy(command[*number_of_segments],segment);
                *number_of_segments += 1;
        }
}
int take_input(int *number_of_segments,char command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_LENGTH])
{
        char input_line[MAX_COMMAND_LENGTH];
        scanf(" %[^\n]%*c",input_line);
        input_line[strcspn(input_line, "\n")] = '\0';
        if(strlen(input_line) == 0)
                return 1;
        seperate_piped(input_line,number_of_segments,command);
        return 0;
}
void seperate_args(int number_of_segments,char command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_LENGTH],char* parsed_command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_ARGS_SIZE])
{
        char* segment;
        char* command_part[MAX_COMMAND_LIST_SIZE];
        for(int i = 0; i < number_of_segments; i++)
        {
                int j = 0;
                *command_part = strdup(command[i]);
                segment = strsep(command_part," ");
                while(segment != NULL)
                {
                        if(strlen(segment) > 0)
                        {
                                parsed_command[i][j] = strdup(segment);
                                j++;
                        }
                        segment = strsep(command_part," ");
                }
                parsed_command[i][j] = NULL;
        }
}
int main()
{
        char *args[] = {"clear",NULL};
        int number_of_segments;
        char command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_LENGTH];
        char* parsed_command[MAX_COMMAND_LIST_SIZE][MAX_COMMAND_ARGS_SIZE];
        execute_command(args);
        print_declaration();
        while(1)
        {
                print_preface();
                int input_check = take_input(&number_of_segments,command);
                if(input_check == 1)
                        continue;

                seperate_args(number_of_segments,command,parsed_command);
                start_process(number_of_segments,parsed_command);
        }
        return 0;
}
