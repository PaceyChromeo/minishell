#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
    int ok;
    pid_t pid;
    int	status;

    ok = 0;
    (void)argc;
    (void)argv;
    (void)envp;
    get_path(); // On recupere le path
   
    do{
      char    *line;

      prompt_color();    
      line = readline("");
      if (line != NULL)
      {
	    pid = fork();
	    if (pid == 0)
	    {
	      system(line); // ici c'est biensur execve qu'il faut employer
	      free (line);
	      line = NULL;
	    }
	    else
	    {
		  waitpid(pid, &status, WUNTRACED); // option wuntraced, le process parent reprend la main si un fils est bloque 
		  free (line);
		  line = NULL;
	    }
      }
      else
      {
	  free((void *)line);
	  line = NULL;
      }
      ok = 1;
     } while(ok);
   return (0);
}
