/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:01:08 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/25 15:18:14 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*collect_id_double_quote(t_lexer *lexer, char *value)
{
	int	i;

	//printf("lexer->index : %d lexer->c : %c\n", lexer->index, lexer->c);
	lexer_next_char(lexer);
	//printf("lexer->index : %d lexer->c : %c\n", lexer->index, lexer->c);
	while (lexer->c != 34 && lexer->c)
	{
		if (lexer->c == '$')
		{
			lexer_next_char(lexer);
			i = lexer->index;
			while (ft_isalpha(lexer->c) || ft_isnum(lexer->c)
				|| lexer->c == '_')
				lexer_next_char(lexer);
			value = ft_realloc(value, get_env(lexer->value, i));
		}
		if (lexer->c != '$' && lexer->c != 34 && lexer->c)
		{
			value = ft_realloc_char(value, lexer->c);
			lexer_next_char(lexer);
		}
		if (!lexer->c)
			return (NULL);
	}
	return (value);
}

static char	*collect_id_single_quote(t_lexer *lexer, char *value)
{
	lexer_next_char(lexer);
	while (lexer->c != 39 && lexer->c)
	{
		if (lexer->c != 39 && lexer->c)
		{
			value = ft_realloc_char(value, lexer->c);
			lexer_next_char(lexer);
		}
		if (!lexer->c)
			return (NULL);
	}
	return (value);
}

char	*collect_id_string(t_lexer *lexer, char *value)
{
	if (lexer->c == 34)
	{
		//printf("lexer->index : %d lexer->c : %c\n", lexer->index, lexer->c);
		value = collect_id_double_quote(lexer, value);
		//printf("lexer->index : %d lexer->c : %c\n", lexer->index, lexer->c);
		if (!value)
		{
			free(value);
			ft_putstr_fd("Unclosed double quotes\n", STDOUT_FILENO);
			return (NULL);
		}
		lexer_next_char(lexer);
	}
	if (lexer->c == 39)
	{
		value = collect_id_single_quote(lexer,value);
		if (!value)
		{
			free(value);
			ft_putstr_fd("Unclosed single quotes\n", STDOUT_FILENO);
			return (NULL);
		}
		lexer_next_char(lexer);
	}
	return (value);
}

char *collect_id_env(t_lexer *lexer, char *value)
{
	int	i;

	i = 0;
	if (lexer->c == '$')
		{
			lexer_next_char(lexer);
			if (lexer->c == ' ')
			{
				value = ft_realloc_char(value, '$');
				return (value);
			}
			i = lexer->index;
			while (ft_isalpha(lexer->c) || ft_isnum(lexer->c) || lexer->c == '_')
				lexer_next_char(lexer);
			value = ft_realloc(value, get_env(lexer->value, i));
	}
	return (value);
}
