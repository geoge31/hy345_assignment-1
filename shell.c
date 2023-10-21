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
      int         pipes_check,redir_check,counter,i;

      pipes_check,redir_check,counter,i = 0;

      token = strtok(str,";");

      while(token)
      {
            pipes_check = hasPipes(token);
            redir_check = hasRedirections(token);

            if(pipes_check > 0)
            {
                  pipeline(token,pipes_check);
                  token = strtok(NULL,";"); 
            }

            else if(redir_check == 1)
            {
                  // printf("Has redirections\n");
                  redirections(token);
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
      char* token;
      char** exec_args;
      int i;

      exec_args = (char**) malloc (sizeof(char*) * MAX_ARGS);

      i=0;

      token = strtok(cmd, " ");
      
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
      int redir_flag,i;

      redir_flag,i = 0;

      while(i < strlen(str))
      {
            if(str[i] == '<' || str[i] == '>')
            {
                  redir_flag = 1;
                  return redir_flag;
            }
            i++;
      }

      return 0;
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



void redirections(char* str)
{
      pid_t       pid;
      char*       input_file;
      char*       output_file;
      char*       token;
      int         status; 

      

      pid = fork();
     
      if(pid < 0)
      {
            perror("fork");
            exit(EXIT_FAILURE);
      }

      else if(pid == 0)
      {                                   /*    Child Process     */
            input_file = NULL;
            output_file = NULL;

            token = strtok(str," ");

            while(token)
            {
                  if(strcmp(token,"<") == 0)
                  {
                       input_file = strtok(NULL," "); 
                  }
                  else if(strcmp(token,">") == 0)
                  {
                       output_file = strtok(NULL," "); 
                  }
                  else 
                  {
                        execlp(token,token,NULL);
                        perror("execlp");
                        exit(EXIT_FAILURE);
                  }

                  token = strtok(NULL, " ");      
            }


            if(input_file)
            {
                  int fd_in = open(input_file, O_RDONLY);

                  if (fd_in == -1) 
                  {
                        perror("open");
                        exit(EXIT_FAILURE);
                  }
                  
                  dup2(fd_in, STDIN_FILENO);
                  close(fd_in);
            }
      
            if(output_file)
            {
                  printf("Output file: %s\n", output_file); // Debugging statement
                  
                  int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                  
                  if (fd_out == -1) 
                  {
                        perror("open");
                        exit(EXIT_FAILURE);
                  }
                  
                  dup2(fd_out, STDOUT_FILENO);
                  close(fd_out);
            }

            execlp(token,token,NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
      }

      else 
      {
            waitpid(pid,&status,0);

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
            {
                  fprintf(stderr, "Command failed with status %d\n", WEXITSTATUS(status));
            }
      }

}