/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:54:36 by pacey             #+#    #+#             */
/*   Updated: 2021/10/14 23:45:52 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_in_string(t_token *token)
{
	int	i;
	int	env;

	env = 0;
	i = -1;
	while (token->value[++i])
	{
		if (token->value[i] == '$')
			env++;
	}
	return (env);
}

static char	*get_env_in_sq(t_token *token, char **env_tab)
{
	int	i;
	int	x;

	x = 0;
	i = -1;
	while (token->value[++i])
	{
		if (token->value[i] == 34 && token->value[i + 1])
		{
			i++;
			while (token->value[i] != 34 && token->value[i])
			{
				if (token->value[i] == '$')
					env_tab[x++] = parser_get_env(token, i);
				i++;
			}
		}
	}
	env_tab[x] = NULL;
	return (rebuild_str_with_env(token, env_tab));
}

static char	*get_env_in_dq(t_token *token, char **env_tab)
{
	int	i;
	int	x;

	x = 0;
	i = -1;
	while (token->value[++i])
	{
		if (token->value[i] == 39 && token->value[i + 1])
		{
			i++;
			while (token->value[i] != 39 && token->value[i])
				i++;
		}
		if (token->value[i] == '$')
			env_tab[x++] = parser_get_env(token, i);
	}
	env_tab[x] = NULL;
	return (rebuild_str_with_env(token, env_tab));
}

char	*parser_get_env(t_token *token, int i)
{
	int		j;
	char	*tok_value;
	char	*env;

	tok_value = NULL;
	j = i;
	while (ft_isalpha(token->value[i]) || token->value[i] == '_')
		i++;
	tok_value = ft_calloc((j - i) + 1, sizeof(char));
	if (!tok_value)
		return (NULL);
	while (j < i)
	{
		tok_value[j] = token->value[j];
		j++;
	}
	tok_value[j] = '\0';
	env = getenv(tok_value);
	if (getenv(env))
		return (env);
	else
	{
		free(tok_value);
		return (NULL);
	}
}

char *get_str_with_env(t_token *token)
{
	char	**env_tab;

	env_tab = ft_calloc(count_env_in_string(token) + 1, sizeof(char *));
	if (!env_tab)
		return (NULL);
	if (token->type == token_string_dq)
		return (get_env_in_dq(token, env_tab));	
	else
		return (get_env_in_sq(token, env_tab));
}