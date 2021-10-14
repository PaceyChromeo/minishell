/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:08:15 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/14 23:49:41 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->current_tok = get_next_token(parser->lexer);
	parser->prev_tok = NULL;
	parser->first_tok = parser->current_tok;
	parser->token_size = 1;
	return (parser);
}

void	parser_next_token(t_parser *parser, int type)
{
	if ((int)parser->current_tok->type == type)
	{
		parser->prev_tok = parser->current_tok;
		parser->current_tok = get_next_token(parser->lexer);
		parser->prev_tok->next = parser->current_tok;
		parser->current_tok->prev = parser->prev_tok;
		if (parser->current_tok->type != token_eof)
			parser->token_size++;
	}
	else
		printf("Unexpected token : %s with type %d\n",
			parser->current_tok->value, parser->current_tok->type);
}

void	parser_define_more_token(t_parser *parser)
{
	int	cmd;

	cmd = 0;
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		if ((parser->current_tok->type > 6 && parser->current_tok->type < 11)
			&& parser->current_tok->next->type == token_id)
			parser->current_tok->next->type = token_file;
		parser->current_tok = parser->current_tok->next;
	}
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		if (parser->current_tok->type == token_id && !cmd)
		{
			parser->current_tok->type = token_cmd;
			cmd++;
		}
		parser->current_tok = parser->current_tok->next;
	}
}

char	*rebuild_str_with_env(t_token *token, char **env_tab)
{
	int	i;
	int	x;

	x = 0;
	i = -1;
	while (token->value[++i])
	{
		env_tab[x++] = token->value;
	}
	return (token->value);
}

void	parser_define_env(t_parser *parser)
{
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		if (parser->current_tok->type == token_env)
		{
			free (parser->current_tok->value);
			parser->current_tok->value = parser_get_env(parser->current_tok, 1);
		}
		if ((parser->current_tok->type == 3 || parser->current_tok->type == 4)
			&& count_env_in_string(parser->current_tok) > 0)
			parser->current_tok->value = get_str_with_env(parser->current_tok);
		parser->current_tok = parser->current_tok->next;
	}
}