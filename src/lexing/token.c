/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:08:31 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/07 15:35:03 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	
	token = malloc(sizeof(t_token) * 1);
	if (!token || !ft_strcmp(value, "\0"))
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token *lexer_next_with_token(t_lexer *lexer, t_token *token)
{
	lexer_next_char(lexer);
	return (token);
}

t_token *lexer_next_with_redir(t_lexer *lexer)
{
	char redir;

	redir = lexer->c;
	lexer_next_char(lexer);
	if (lexer->c == redir)
	{
		lexer_next_char(lexer);
		if (lexer->c == redir)
			return (NULL);
		else if (redir == 60)
			return (init_token(token_dred_l, "<<"));
		else
			return (init_token(token_dred_r, ">>"));
	}
	else
	{
		if (redir == 60)
			return (init_token(token_sred_l, get_char_as_string('<')));
		else
			return (init_token(token_sred_r, get_char_as_string('>')));
	}
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
		if (lexer->c == '>' || lexer->c == '<')
			return (lexer_next_with_redir(lexer));
		if (lexer->c == '(')
		 	return (lexer_next_with_token(lexer, init_token(token_lparen, get_char_as_string('('))));
		if (lexer->c == ')')
		 	return (lexer_next_with_token(lexer, init_token(token_rparen, get_char_as_string(')'))));
	}
	return (init_token(token_eof, "\0"));
}
