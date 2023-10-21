/*  
    #######################################################
    #                                                     #
    #           Assignment 1 - hy345                      # 
    #           Giogos Geramoutsos, @csd3927              #
    #                                                     #
    #######################################################                                                           
*/

#include"shell.h"

int main(int argc, char *argv[]) {

    char str_input[MAX_INPUT_SIZE];
    char *token;

    while(TRUE) 
    {
        print_command_prompt();

        fgets(str_input, MAX_INPUT_SIZE, stdin);

        str_input[strlen(str_input) - 1] = '\0';

        handle_input(str_input);
    }

    return 0;
}
