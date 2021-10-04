#include "minishell.h"

char *prompt(char *invite)
{
    invite = getenv("LOGNAME");
    if (invite == NULL)
    {
        invite = getenv("USERNAME");
        if (invite == NULL)
        {
            invite = "";
        }
    }
    invite = ft_strjoin(invite, "@");
    invite = ft_strjoin(invite, getenv("NAME"));
 
   return (invite);
}

void   prompt_color()
 {
    char    *invite;
    char const  *absolute_p;
    char        **relative_p;

    invite = NULL;
    invite = malloc(sizeof(invite));
    invite = prompt(invite);
    blue();
    printf("%s", invite);
    reset();
    absolute_p = getenv("PWD");
    if (absolute_p == NULL)
    {
        absolute_p = "";
    }   
    relative_p = ft_split(absolute_p, '/'); 
    yellow();
    printf(":~/%s", relative_p[2]);
    reset();
    printf("$ ");
 }