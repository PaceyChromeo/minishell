/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:08:31 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/29 12:13:57 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

static	t_token	*lexer_collect_redir(t_lexer *lexer)
{
	char	redir;

	redir = lexer->c;
	lexer_next_char(lexer);
	if (lexer->c == redir)
	{
		lexer_next_char(lexer);
		if (lexer->c == redir)
			return (init_token(token_error, NULL));
		else if (redir == 60)
			return (init_token(token_dred_l, ft_strdup("<<")));
		else
			return (init_token(token_dred_r, ft_strdup(">>")));
	}
	else
	{
		if (redir == 60)
			return (init_token(token_sred_l, ft_strdup("<")));
		else
			return (init_token(token_sred_r, ft_strdup(">")));
	}
}

t_token	*get_next_token(t_lexer	*lexer)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->value))
	{
		if (lexer->c == ' ')
			lexer_next_char(lexer);
		if (ft_is_ascii(lexer->c) && (lexer->c != '$' && lexer->c != '>'
			&& lexer->c != '<'))
			return (lexer_collect_id(lexer));
		if (lexer->c == '$')
			return (lexer_collect_env(lexer));
		if (lexer->c == '>' || lexer->c == '<')
			return (lexer_collect_redir(lexer));
	}
	return (init_token(token_eof, NULL));
}
