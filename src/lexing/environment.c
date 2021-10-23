/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:54:36 by pacey             #+#    #+#             */
/*   Updated: 2021/10/22 18:35:36 by pacey            ###   ########.fr       */
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

char	*get_env(char *token_value, int i)
{
	char	*env;
	int		size;
	int		x;

	x = 0;
	size = i;
	if (ft_isalpha(token_value[size]) || token_value[size] == '_')
		size++;
	while (ft_isalpha(token_value[size]) || token_value[size] == '_'
		|| ft_isnum(token_value[size]))
		size++;
	env = ft_calloc((size - i) + 1, sizeof(char));
	if (!env)
		return (NULL);
	while (i < size)
	{
		env[x] = token_value[i];
		i++;
		x++;
	}
	env[x] = '\0';
	token_value = getenv(env);
	free(env);
	return (token_value);
}

static int	count_total_string(t_token *token)
{
	int		i;
	int		size;
	char	*tok_value;
	char	*env;

	size = 0;
	i = 0;
	tok_value = ft_strdup(token->value);
	while (tok_value[i])
	{
		if (tok_value[i] == '$')
		{
			i++;
			env = get_env(tok_value, i);
			size += ft_strlen(env);
			while ((ft_isalpha(tok_value[i]) || tok_value[i] == '_'
					|| ft_isnum(tok_value[i])))
				i++;
			if (!tok_value[i])
			{
				free(tok_value);
				return (size);
			}
			if (tok_value[i] == '$' && !tok_value[i + 1])
			{
				free(tok_value);
				return (size + 1);
			}
		}
		if (tok_value[i] != '$')
		{
			i++;
			size++;
		}
	}
	free(tok_value);
	return (size);
}

static char	*str_with_env(t_token *token, char *str_with_env, int size)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		while (token->value[i] == '$')
		{
			i++;
			str_with_env = ft_realloc(str_with_env, get_env(token->value, i));
			while (ft_isalpha(token->value[i]) || token->value[i] == '_'
				|| ft_isnum(token->value[i]))
				i++;
			if (!token->value[i])
			{
				str_with_env[size] = '\0';
				return (str_with_env);
			}
			if (token->value[i] == '$' && !token->value[i + 1])
			{
				str_with_env[size - 1] = '$';
				str_with_env[size] = '\0';
				return (str_with_env);
			}
		}
		str_with_env = ft_realloc_char(str_with_env, token->value[i]);
		i++;
	}
	str_with_env[size] = '\0';
	return (str_with_env);
}

char	*get_str_with_env(t_token *token)
{
	char	*string_with_env;
	int		size;

	size = count_total_string(token);
	string_with_env = ft_calloc(size + 1, sizeof(char *));
	if (!string_with_env)
		return (NULL);
	string_with_env = str_with_env(token, string_with_env, size);
	return (string_with_env);
}
