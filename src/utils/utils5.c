/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:13:52 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/02 12:40:58 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_exportargs(char *str)
{
	int	i;
	int	equal;

	equal = 0;
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while ((ft_isalpha(str[i]) || ft_isnum(str[i]) || str[i] == '_')
			&& str[i])
			i++;
		if (str[i] == '=')
		{
			equal++;
			return (1);
		}
	}
	return (0);
}

int	count_total_string(t_token *token, t_var *var)
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
			env = get_env(tok_value, i, var);
			if (env)
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
