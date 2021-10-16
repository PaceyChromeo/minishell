/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:03:08 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/16 21:39:29 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt(char *invite)
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
	invite = ft_realloc(invite, getenv("USERNAME"));
	return (invite);
}

char	*prompt_color(void)
{
	char const	*absolute_p;
	char		**relative_p;
	char		*invite;

	invite = NULL;
	invite = prompt(invite);
	absolute_p = getenv("PWD");
	if (absolute_p == NULL)
	{
		absolute_p = "";
	}
	relative_p = ft_split(absolute_p, '/');
	invite = ft_realloc(invite, ":~/");
	invite = ft_realloc(invite, relative_p[2]);
	invite = ft_realloc(invite, "$ ");
	free_tab(relative_p);
	return (invite);
}
