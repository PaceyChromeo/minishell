/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:12:21 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/05 16:12:10 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *value)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer) * 1);
	if (!lexer)
		return (NULL);
	lexer->index = 0;
	lexer->value = value;
	lexer->c = value[lexer->index];
	return(lexer);
}

void	lexer_next_char(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->value))
	{
		lexer->index += 1;
		lexer->c = lexer->value[lexer->index];
	}
}

t_token	*lexer_collect_cmd(t_lexer *lexer)
{
	char	*value;
	char	*c;
	char	*tmp;

	value = NULL;
	tmp = NULL;
	while (ft_isalpha(lexer->c))
	{
		c = get_char_as_string(lexer);
		if (value)
		{
			tmp = value;
			free(value);
			value = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(c)));
			if (!value)
				return (NULL);
			value = ft_strcat(tmp, c);
		}
		else
			value = c;
		lexer_next_char(lexer);
	}
	return (init_token(token_cmd, value));
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	t_token	*string;

	string = malloc(sizeof(t_token) * 1);
	if (!string)
		return (NULL);
	string->value = lexer->value;
	return (string);
}

char	*get_char_as_string(t_lexer *lexer)
{
	char	*s;

	s = malloc(sizeof(char) * 2);
	if (!s)
		return (NULL);
	s[0] = lexer->c;
	s[1] = '\0';
	return (s);
}