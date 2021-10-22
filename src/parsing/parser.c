/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:08:15 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/22 13:48:04 by pjacob           ###   ########.fr       */
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
	return (parser);
}

void	parser_next_token(t_parser *parser)
{
	parser->prev_tok = parser->current_tok;
	parser->current_tok = get_next_token(parser->lexer);
	parser->prev_tok->next = parser->current_tok;
	parser->current_tok->prev = parser->prev_tok;
}

void	parser_define_more_token(t_parser *parser)
{
	int	cmd;

	cmd = 0;
	parser->current_tok = parser->first_tok;
	while (parser->current_tok)
	{
		if ((parser->current_tok->type > 6 && parser->current_tok->type < 11)
			&& parser->current_tok->next->type == token_id)
			parser->current_tok->next->type = token_file;
		parser->current_tok = parser->current_tok->next;
	}
	parser->current_tok = parser->first_tok;
	while (parser->current_tok)
	{
		if (parser->current_tok->type == token_id && !cmd)
		{
			parser->current_tok->type = token_cmd;
			cmd++;
		}
		parser->current_tok = parser->current_tok->next;
	}
}

void	parser_get_token_with_env(t_parser *parser)
{
	char	*tmp;

	parser->current_tok = parser->first_tok;
	while (parser->current_tok)
	{
		if (parser->current_tok->type == token_string_dq)
		{
			if (count_env_in_string(parser->current_tok))
			{
				tmp = parser->current_tok->value;
				parser->current_tok->value
					= get_str_with_env(parser->current_tok);
				free(tmp);
			}
		}
		if (parser->current_tok->type == token_env
			&& (ft_strcmp(parser->current_tok->value, "$?")
			&& ft_strcmp(parser->current_tok->value, "$")))
		{
			tmp = parser->current_tok->value;
			parser->current_tok->value
				= get_str_with_env(parser->current_tok);
			free(tmp);
		}
		parser->current_tok = parser->current_tok->next;
	}
}
