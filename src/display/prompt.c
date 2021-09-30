#include "minishell.h"

char *prompt(char *invite)
{
    char    *user = NULL;
    char    *host = NULL;
    char    *absolute_p = NULL;
 //   char    **relative_p = NULL;

    user = getenv("USERNAME");
    if (user == NULL)
    {
        user = getenv("USER");
        if (user == NULL)
            user = "";
    }
	host = getenv("NAME");
    if (host == NULL)
		host = "";
	absolute_p = getenv("PWD");
	if (absolute_p == NULL)
		absolute_p = "";
	//relative_p = ft_split(absolute_p, '/');
	invite = (char *)malloc(sizeof(*invite) * (ft_strlen(user) + ft_strlen(host) + ft_strlen(absolute_p) + 7));
	if (!invite)
		return (NULL);
	ft_strcat(invite, user);
	ft_strcat(invite, "@");
	ft_strcat(invite, host);
	ft_strcat(invite, ":~/");
	//ft_strcat(invite, relative_p[2]);
	ft_strcat(invite, "$>");
	ft_strcat(invite, " ");
	return (invite);
}

void   prompt_color()
 {
    char    *invite;
    //char    **tab_prompt;

    invite = NULL;
    invite = prompt(invite);
    if (invite != NULL)
    {
        //tab_prompt = ft_split(invite, ':');
        blue();
        //printf("%s", tab_prompt[0]);
        reset();
        printf("%c", ':');
        yellow();
        //printf("%s", tab_prompt[1]);
        reset();
        free (invite);
        invite = NULL;
    }
 }