#include "minishell.h"

int count_pipe(char *line)
{
    int i;
    int pipe;

    i = 0;
    pipe = 0;
    while(line[i] != '\0')
    {
        if (line[i] == '|')
            pipe += 1;
        i++;
    }
    return (pipe);
}

