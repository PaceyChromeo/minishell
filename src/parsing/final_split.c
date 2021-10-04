  #include "minishell.h"

static int  nbr_tab(char **dst)
{
    int i;

    i = 0;
    while (dst[i])
        i++;
    return (i);
}

char  ***final_split(char *s, char c)
  {  
    char    **dst;
    char    ***d;
    int     total;
    int     i;
    
    dst = NULL;
    d = NULL;
    total = 0;
    i = 0;
    dst = ft_split_pipe(s, c);
    total = nbr_tab(dst);
    d = (char ***)malloc(sizeof(char **) * total + 1);
    while (i < total)
    {
        d[i] = ft_split_space(dst[i], ' ');
        i++;
    }
    d[i] = 0;
    return (d);
  }