#include "minishell.h"

static char *prompt(char *invite)
{
    invite = getenv("USER");
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

int	prompt_color()
{
    char        *invite;
    char const  *absolute_p;
    char        **relative_p;

    invite = NULL;
    invite = prompt(invite);
    blue();
    printf("%s", invite);
    white();
	absolute_p = getenv("PWD");
	if (absolute_p == NULL)
	{
		absolute_p = "";
	}   
	relative_p = ft_split(absolute_p, '/'); 
	yellow();
	printf(":~/%s", relative_p[2]);
	white();
	printf("$ ");
	return (0);
 }