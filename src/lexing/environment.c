/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:54:36 by pacey             #+#    #+#             */
/*   Updated: 2021/10/15 15:45:05 by pacey            ###   ########.fr       */
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

int	check_quote_surround(t_token *token, int i)
{
	int	quote;
	int	j;

	j = i;
	while ((token->value[i] != 34 && token->value[i] != 39) && i >= 0)
		i--;
	if (i < 0)
		return (0);
	quote = (int)token->value[i];
	while ((token->value[j] != 34 && token->value[j] != 39) && token->value[j])
		j++;
	if (quote == token->value[j])
		return (quote);
	else
		return (0);
}

static char	*get_env(t_token *token, int i)
{
	char	*env;
	int		size;
	int		x;

	x = 0;
	size = i;
	while (ft_isalpha(token->value[size]) || token->value[size] == '_')
		size++;
	env = ft_calloc((size - i) + 1, sizeof(char));
	if (!env)
		return (NULL);
	while (i < size)
	{
		env[x] = token->value[i];
		i++;
		x++;
	}
	env[x] = '\0';
	return (getenv(env));
}

int	count_total_string(t_token *token)
{
	int	i;
	int	size;

	size = 0;
	i = -1;
	while (token->value[++i])
	{
		if (token->value[i] == 34 && ((token->type == token_id
			|| token->type == token_string_dq) && check_quote_surround(token, i) != 39))
			i++;
		if (token->value[i] == '$' && (check_quote_surround(token, i) == 34
			|| (token->type == token_string_dq && check_quote_surround(token, i) != 39)))
		{
			i++;
			size += ft_strlen(get_env(token, i));
			while (ft_isalpha(token->value[i]) || token->value[i] == '_')
				i++;
			while ((token->value[i] != 34 || token->value[i] != '$') && token->value[i])
			{
				i++;
				size++;
			}
		}
		size++;
	}
	return (size);
}

char	*get_str_with_env(t_token *token)
{
	char	*string_with_env;
	int		size;
	int		i;

	i = -1;
	size = count_total_string(token);
	string_with_env = ft_calloc(size + 1, sizeof(char *));
	if (!string_with_env)
		return (NULL);
	while (token->value[++i])
	{
		if (token->value[i] == 34 && ((token->type == token_id
			|| token->type == token_string_dq) && check_quote_surround(token, i) != 39))
			i++;
		if (token->value[i] == '$' && (check_quote_surround(token, i) == 34
			|| (token->type == token_string_dq && check_quote_surround(token, i) != 39)))
		{
			i++;
			string_with_env = ft_realloc(string_with_env, get_env(token, i));
			while (ft_isalpha(token->value[i]) || token->value[i] == '_')
				i++;
		}
		if (token->value[i] == 34 && ((token->type == token_id
			|| token->type == token_string_dq) && check_quote_surround(token, i) != 39))
			i++;
		string_with_env = ft_realloc_char(string_with_env, token->value[i]);
	}
	string_with_env[size] = '\0';
	return (string_with_env);
}