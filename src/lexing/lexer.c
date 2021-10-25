/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:12:21 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/25 15:14:14 by hkrifa           ###   ########.fr       */
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
		//printf("lexer->c : %c lexer->value[%d] : %c\n", lexer->c, lexer->index, lexer->value[lexer->index]);
		if (((lexer->c == 34 && lexer->value[lexer->index + 1] != 34)
			|| (lexer->c == 39 && lexer->value[lexer->index + 1] != 39))
			&& lexer->value[lexer->index + 1])
		{
			value = collect_id_string(lexer, value);
			if (!value)
				return (init_token(token_error, NULL));
		}
		else if (((lexer->c == 34 && lexer->value[lexer->index + 1] == 34)
			|| (lexer->c == 39 && lexer->value[lexer->index + 1] == 39))
			&& lexer->value[lexer->index + 1])
		{
			lexer_next_char(lexer);
			lexer_next_char(lexer);
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
