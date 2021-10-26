/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:12:21 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/26 11:42:28 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *value)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->index = 0;
	lexer->value = value;
	lexer->c = value[lexer->index];
	return (lexer);
}

void	lexer_next_char(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->value))
	{
		lexer->index += 1;
		lexer->c = lexer->value[lexer->index];
	}
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;

	value = NULL;
	while (lexer->c != ' ' && lexer->c != '\0'
		&& lexer->c != '<' && lexer->c != '>')
	{
		if (lexer->c == 34 || lexer->c == 39)
		{
			value = collect_id_string(lexer, value);
			if (value && !ft_strcmp(value, "error_quote"))
				return (init_token(token_error, NULL));
		}
		else if (lexer->c == '$')
			value = collect_id_env(lexer, value);
		else
		{
			value = ft_realloc_char(value, lexer->c);
			lexer_next_char(lexer);
		}
	}
	return (init_token(token_id, value));
}

t_token	*lexer_collect_env(t_lexer *lexer)
{
	char	*value;

	value = NULL;
	while (lexer->c == '$')
	{
		value = ft_realloc_char(value, lexer->c);
		lexer_next_char(lexer);
		if (lexer->c == ' ' || !lexer->c)
		{
			lexer_next_char(lexer);
			return (init_token(token_env, value));
		}
		else if (!ft_isalpha(lexer->c) && lexer->c != '_' && lexer->c != '?')
			return (init_token(token_env, value));
		else if (lexer->c == '?')
		{
			value = ft_realloc_char(value, lexer->c);
			lexer_next_char(lexer);
			return (init_token(token_env, value));
		}
		while (ft_isalpha(lexer->c) || lexer->c == '_' || ft_isnum(lexer->c))
		{
			value = ft_realloc_char(value, lexer->c);
			lexer_next_char(lexer);
		}
	}
	return (init_token(token_env, value));
}
