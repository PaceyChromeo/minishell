/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:08:31 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/05 16:12:52 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * 1);
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token	*get_next_token(t_lexer	*lexer)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->value))
	{
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_next_char(lexer);
		if (ft_isalpha(lexer->c))
			return (lexer_collect_cmd(lexer));
		if (lexer->c == 34 || lexer->c == 39)
			return (lexer_collect_string(lexer));
		// if (lexer->c == '>' || lexer->c == '(' || lexer->c == ')')
		// 	return (lexer_next_with_token(lexer));
			
	}
	return (init_token(token_eof, "\0"));
}
