/*  
      #######################################################
      #                                                     #
      #           Assignment 1 - hy345                      # 
      #           Giogos Geramoutsos, @csd3927              #
      #                                                     #
      #######################################################                                                           
*/

#include"shell.h"


void print_command_prompt()
{
      char cwd[1024]; 
      char *dirPath;
      char *userName;

      dirPath = NULL;
      userName = NULL;

    //   dirPath = (char*) malloc (sizeof(char));
    //   userName = (char* )malloc (sizeof(char));
    //   userName = getlogin();

    //   if(userName==NULL)
    //   {
    //         perror("NO USER FOUND");
    //         exit(EXIT_FAILURE);
    //   } 
    //   else 
    //   {
            dirPath = getcwd(cwd,sizeof(cwd));
            printf("csd3927-hy345sh@%s:%s$ ",userName,dirPath);
    //   } 
     
}



void handle_input(char* str)
{     
      char*       token;
      char**      argmts;
      int         pipes_check,redir_check,counter,i;

      pipes_check,redir_check,counter,i = 0;

      token = strtok(str,";");
      
      while(token)
      {
            // printf("token\t%s\n",token);  //debug

            pipes_check = hasPipes(token);
            // printf("Pipes\t%d\n",pipes_check);  // debug

            redir_check = hasRedirections(token);
            // printf("Redirection\t%d\n",redir_check);  //debug

            if(pipes_check > 0)
            {
                  pipeline(token,pipes_check);
                  token = strtok(NULL,";"); 
            }

            else if(redir_check > 0)
            {
                  redirections(token,redir_check);
                  token = strtok(NULL,";");
            }

            else
            {
                  if(strcmp(token,"exit") ==0)
                  {
                        exit(EXIT_SUCCESS);
                  }

                  fork_process(token);

                  token = strtok(NULL,";"); 
            }

            
      }

}



void fork_process(char* cmd)
{
      pid_t       pid;
      char**      cmd_arguments;

      cmd_arguments = NULL;

         pid = fork();

         if(pid < 0)
         {
            perror("FORKING FAILURE");
            exit(EXIT_FAILURE);
         }

         else if(pid == 0)
         {
            cmd_arguments = set_arguments(cmd);
            execute_process(cmd_arguments);
            free(cmd_arguments);  
         }

         else
         {
            waitpid(pid,NULL,0);
         }
}



char** set_arguments(char* cmd)
{
      char*       token;
      char**      exec_args;
      int         i;

      exec_args = (char**) malloc (sizeof(char*) * MAX_ARGS);

      i=0;

      token = strtok(cmd," ");
      
      if(exec_args)
      {
            while(token)
            {
                  exec_args[i] = token;
                  token = strtok(NULL," ");
                  i++;
            }

            exec_args[i] = NULL;

            return exec_args;
      }

      else
      {
            return NULL;
      }   
}



void execute_process(char* exec_args[MAX_ARGS])
{
      if(execvp(exec_args[0],exec_args) == -1)
      {
            perror("EXECUTION FAILED");
            exit(EXIT_FAILURE);
      }
}



int hasPipes(char *str)
{
      int pipe_counter,i;

      pipe_counter,i = 0;

      while(i < strlen(str))
      {
            if(str[i] == '|')
            {
                pipe_counter++;
            }

            i++;
      }

      return pipe_counter;
}



int hasRedirections(char* str)
{
      /*
            int redir_flag,i;

            redir_flag,i = 0;

            while(i < strlen(str))
            {
                  if(str[i] == '<' || str[i] == '>' || str[i] == '>>')
                  {
                        redir_flag = 1;
                        return redir_flag;
                  }
                  i++;
            }

            return 0;
      */

      char* in;
      char* out;
      char* app;

      in = strstr(str,"<");
      out = strstr(str,">");
      app = strstr(str,">>");

      if(in)
      {
            return 1;
      }
      else if(out)
      {
            return 2;
      }
      else if(app){
            return 3;
      }
      else 
      {
            return 0;
      }
}



void pipeline(char *pipesString, int totalPipes)
{
      // char*       token;
      // char**      cmd_arguments;
      // int         pipesArr[totalPipes][2];
      // int         i,j,processes;
      // pid_t       pid[totalPipes];

      // i,j = 0;
      // processes = totalPipes + 1;

      // cmd_arguments = (char** )malloc(sizeof(char*) * MAX_ARGS);

      // token = strtok(pipesString,"|");

      // for(i=0; i<totalPipes; i++)           
      // {                                                 /* Create the pipes for the processes */
      //       if(pipe(pipesArr[i]) < 0)
      //       {
      //             perror("PIPE FAILURE here");
      //             exit(EXIT_FAILURE);
      //       }
      // }

      // for(i=0; i<processes; i++)
      // {                                               /* Fork for all the process needed */

      //       pid[i] = fork();

            

      //       if(pid[i] < 0)
      //       {
      //             perror("FORK FAILURE");
      //             exit(EXIT_FAILURE);
      //       }

      //       if(pid[i] == 0)  
      //       {
                  
      //             cmd_arguments = set_arguments(token);
                  
      //             // 1h diergasia
      //             if((i == 0))
      //             {
      //                   dup2(pipesArr[i][1],STDOUT_FILENO);

      //                   // close(pipesArr[i][0]);

      //                   for(j=0; j<totalPipes; j++)
      //                   {
      //                         // if(j != 0)
      //                         // {
      //                               close(pipesArr[j][0]);
      //                               close(pipesArr[j][1]);
      //                         // }
      //                   }
 
      //                   execute_process(cmd_arguments);
      //             }

      //             //  teleutaia diergasia
      //             else if(i == totalPipes)
      //             {
      //                   dup2(pipesArr[i-1][0],STDIN_FILENO);

      //                   for(j=0; j<totalPipes; j++)
      //                   {
      //                         // if(j != totalPipes-1)
      //                         // {
      //                               close(pipesArr[j][0]);
      //                               close(pipesArr[j][1]);
      //                         // }
      //                   }

      //                   // close(pipesArr[j-1][1]);
      //                   execute_process(cmd_arguments);
      //             } 

      //             // ypoloipes
      //             else
      //             {
      //                   dup2(pipesArr[i-1][0],STDIN_FILENO);
      //                   dup2(pipesArr[i][1],STDOUT_FILENO);

      //                   for(j=0; j<totalPipes; j++)
      //                   {
      //                         // // close all the pipes
      //                         close(pipesArr[j][0]);
      //                         close(pipesArr[j][1]);
      //                   }

      //                   // close(pipesArr[i-1][1]); // Close write end
      //                   // close(pipesArr[i][0]);   // Close read end

                        
      //                   // close pipes

      //                   execute_process(cmd_arguments);
      //             }    
      //       }
            
      //       token = strtok( NULL,"|");
      // }

     
      // for(i=0; i<processes; i++)
      // {
      //       waitpid(pid[i],NULL,0);
      // }

      // for(i=0; i<totalPipes; i++)
      // {
      //       // close all the pipes
      //       close(pipesArr[i][0]);
      //       close(pipesArr[i][1]);
      // }

}



void redirections(char* str, int redir_flag)
{
      char*       token;
      char*       token2;
      char*       token3;
      char**      argmnts;

      token = NULL;
      token2 = NULL;
      argmnts = NULL;

      switch(redir_flag)
      {
            case 1:
                        token = strtok(str,"<");
                        argmnts = set_arguments(token);
                        token = strtok(NULL,"<");
                        break;
            case 2:
                        token = strtok(str,">");
                        token2 = strtok(NULL,">");
                        argmnts = set_arguments(token);
                        break;
            case 3:     
                        token = strtok(str,">>");
                        argmnts = set_arguments(token);
                        token = strtok(NULL,">>");
                        break;
            default:
                        break;
      }
      
      token3 = removeSpaces(token2);  

      execute_redirections(argmnts,token3,redir_flag);
}



void execute_redirections(char** cmd1, char* cmd2, int redir)
{
      pid_t pid;

      if(redir != 0)
      {
            if(redir == 1)
            {
                  int fd = open(cmd2, O_RDONLY); 

                  if(fd == -1)
                  {
                        perror("open");
                        exit(EXIT_FAILURE);
                  }  

                  dup2(fd, STDIN_FILENO);
                  close(fd);
            }
            
            if(redir == 2)
            {
                  int fd = open(cmd2, O_WRONLY | O_CREAT | O_TRUNC, 0666);

                  if(fd == -1)
                  {
                        perror("open");
                        exit(EXIT_FAILURE);  
                  }
                  dup2(fd,STDOUT_FILENO);
                  close(fd);
            }
      }

      pid = fork();

      if(pid < 0)
      {
            perror("FORK FAILURE");
            exit(EXIT_FAILURE);
      }

      else if(pid == 0)
      {
            if(execvp(cmd1[0],cmd1) == -1 )
            {
                  perror("EXECUTION FAILURE");
                  exit(EXIT_FAILURE);
            }
      }

      else
      {
            wait(NULL);
      }
}



char* removeSpaces(char* input)
{
    
    int i = 0, j = 0;
    while (input[i]) {
        if (input[i] != ' ') {
            input[j++] = input[i];
        }
        i++;
    }
    input[j] = '\0';

    return input;
}


