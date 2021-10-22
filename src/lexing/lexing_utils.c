/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:01:08 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/22 17:17:15 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*collect_id_single_quote(t_lexer *lexer, char *value)
{
	int	i;

	lexer_next_char(lexer);
	while (lexer->c != 34 && lexer->c)
	{
		if (lexer->c == '$')
		{
			lexer_next_char(lexer);
			i = lexer->index;
			while (ft_isalpha(lexer->c) || ft_isnum(lexer->c) || lexer->c == '_')
				lexer_next_char(lexer);
			value = ft_realloc(value, get_env(lexer->value, i));
		}
		if (!lexer->c)
		{
			free(value);
			return (NULL);
		}
		if (lexer->c != '$' && lexer->c != 34)
			value = ft_realloc_char(value, lexer->c);
		lexer_next_char(lexer);
	}
	return (value);
}

char	*collect_id_double_quote(t_lexer *lexer, char *value)
{
	lexer_next_char(lexer);
	while (lexer->c != 39 && lexer->c)
	{
		value = ft_realloc_char(value, lexer->c);
		lexer_next_char(lexer);		
		if (!lexer->c)
		{
			free(value);
			return (NULL);
		}
		if (lexer->c != 39)
			value = ft_realloc_char(value, lexer->c);
		lexer_next_char(lexer);
	}
	return (value);
}