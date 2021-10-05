#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char **dst = NULL;
	char ***d = NULL;
	int res = 0;
	int i = 0;
	int j = 0;
	//int cmd = -1;

	int		ok;
	char	*line;
	char    *step1;
	char    *step2;
	// pid_t	pid;

	ok = 1;
	(void)argc;
	(void)argv;
	(void)envp;	
	while (ok)
	{
		// prompt_color();   
    
        line = readline("");
		if (line != NULL)
		{
            res = check_quote(line);
            if (res == 1)
                printf("Syntax Error\n");
            else
            {
                printf("syntax ok\n");
                printf("original:  %s\n", line);
                step1 = clean_redirection(line);
                step2 = clean_quotes(step1);
                yellow();
                printf("cleaned: %s\n", step2);
                reset();
                printf("-----------------\n");

                dst = ft_split_pipe(step2, '|');
                while (dst[i])
                {
                    printf("line %d:  %s\n",i + 1, dst[i]);
                    i++;
                }
                i = 0;
                printf("-----------------\n");

                d = final_split(step2, '|');
                while (d[i])
                {
                    j = 0;
                    while (d[i][j])
                    {
                        printf("part %d: %s\n",j + 1, d[i][j]);
                       /*  if (j == 0)
                        {
                            cmd = check_cmd(d[i][j]);
                            if (cmd == 0)
                                printf("command is a builtin\n");
                        } */
                        j++;
                    }
                    printf("-----------------\n");
                    i++;
                }
            }
			add_history(line);
        //     i = 0;
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		system(line);
		// 	 	free (line);
		// 	 	line = NULL;
		// 	}
		// 	else
		// 	{
		// 	 	waitpid(pid, &status, WUNTRACED); // option wuntraced, le process parent reprend la main si un fils est bloque 
		// 	 	free (line);
		// 	 	line = NULL;
		// 	}
		}
    }
    return (0);
}
