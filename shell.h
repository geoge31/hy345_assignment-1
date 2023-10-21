/*  
      #######################################################
      #                                                     #
      #           Assignment 1 - hy345                      # 
      #           Giogos Geramoutsos, @csd3927              #
      #                                                     #
      #######################################################                                                           
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h> 
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_INPUT_SIZE    1024
#define MAX_ARGS    512
#define TRUE    1

void print_command_prompt();                                      /* print the command prompt */

void handle_input(char* str);                                     /* parse input and begin fork progress */

void fork_process(char* cmd);                                     /* forks a process */

char** set_arguments(char* cmd);                                  /* set the arguments of the command to be executed*/

void execute_process(char* exec_args[MAX_ARGS]);                  /*executes command  */

int hasPipes(char *str);                                          /*checks if there is any pipe in the command*/

int hasRedirections(char* str);                                   /* checks if there is any redirection in the command */

void pipeline(char *pipesString, int totalPipes);

void redirections(char* str);



// void pipes_implementation(char *str, int npipes, char* exec_args[MAX_ARGS]);



