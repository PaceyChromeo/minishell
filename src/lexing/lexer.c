/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:12:21 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/11 10:10:25 by pjacob           ###   ########.fr       */
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
	while (lexer->c != 32 && lexer->c != 34 && lexer->c != 39 && lexer->c != 36
		&& lexer->c != '\0' && lexer->c != '(' && lexer->c != ')')
	{
		value = ft_realloc_char(value, lexer);
		lexer_next_char(lexer);
	}
	return (init_token(token_id, value));
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	char	quote;
	char	*value;

	quote = lexer->c;
	value = NULL;
	lexer_next_char(lexer);
	while (lexer->c != quote)
	{
		value = ft_realloc_char(value, lexer);
		lexer_next_char(lexer);
		if (lexer->c == '\0')
		{
			free(value);
			return (init_token(token_eof, NULL));
		}
	}
	lexer_next_char(lexer);
	if (quote == 34)
		return (init_token(token_string_dq, value));
	else
		return (init_token(token_string_sq, value));
}

t_token	*lexer_collect_env(t_lexer *lexer)
{
	char	*value;

	value = NULL;
	lexer_next_char(lexer);
	while (ft_isalpha(lexer->c) || lexer->c == '_')
	{
		value = ft_realloc_char(value, lexer);
		lexer_next_char(lexer);
	}
	return (init_token(token_env, value));
}
