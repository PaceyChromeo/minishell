#include "minishell.h"

char *prompt(void)
{
	char		*invite;
	const char	*user;
	const char	*host;
	const char	*absolute_p;
	char		**relative_p;

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
	relative_p = ft_split(absolute_p, '/');
	invite = malloc(sizeof(*invite) * 256);
	if (!invite)
		return (NULL);
	ft_strcat(invite, user);
	ft_strcat(invite, "@");
	ft_strcat(invite, host);
	ft_strcat(invite, ":~/");
	ft_strcat(invite, relative_p[2]);
	ft_strcat(invite, "$>");
	ft_strcat(invite, " ");
	return (invite);
}

int	prompt_color()
 {
    char    *invite;
    char    **tab_prompt;

	invite = prompt();
    if (invite != NULL)
    {
        tab_prompt = ft_split(invite, ':');
        blue();
        printf("%s", tab_prompt[0]);
        reset();
        printf("%c", ':');
        yellow();
        printf("%s", tab_prompt[1]);
        reset();
        free (invite);
        invite = NULL;
		return (1);
    }
	else
		return (0);
 }