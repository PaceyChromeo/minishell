/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:08:15 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/12 15:40:31 by pacey            ###   ########.fr       */
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

// static void	define_token_file(t_parser *parser)
// {
// 	parser->current_tok = parser->first_tok;
// 	while (parser->current_tok->type != token_eof)
// 	{
// 		if ((parser->current_tok->type > 6 && parser->current_tok->type < 11)
// 			&& parser->current_tok->next->type == token_id)
// 			parser->current_tok->next->type = token_file;
// 		parser->current_tok = parser->current_tok->next;
// 	}
// }

// static void	define_token_cmd(t_parser *parser)
// {
	
// 	parser->current_tok = parser->first_tok;
// 	while (parser->current_tok->type != token_eof)
// 	{
// 		printf("str to compare : %s with result : %d\n", parser->current_tok->value, cmp_builtins(parser->current_tok->value));
// 		if (cmp_builtins(parser->current_tok->value) < 7 && !cmd)
// 		{
// 			parser->current_tok->type = token_cmd;
// 			cmd++;
// 		}
// 		parser->current_tok = parser->current_tok->next;
// 	}
// }

void	parser_define_more_token(t_parser *parser)
{
	int	cmd;

	cmd = 0;
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		printf("str to compare : %s with result : %d\n", parser->current_tok->value, cmp_builtins(parser->current_tok->value));
		if (cmp_builtins(parser->current_tok->value) < 7 && !cmd)
		{
			parser->current_tok->type = token_cmd;
			cmd++;
		}
		parser->current_tok = parser->current_tok->next;
	}
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		if ((parser->current_tok->type > 6 && parser->current_tok->type < 11)
			&& parser->current_tok->next->type == token_id)
			parser->current_tok->next->type = token_file;
		parser->current_tok = parser->current_tok->next;
	}
	// while (parser->current_tok->value)
	// {
	// 	if (parser->current_tok->type > 6 && parser->current_tok->type < 11)
	// 	{
	// 		break ;
	// 	}
	// 	parser->current_tok = parser->current_tok->next;
	// }
	// define_token_file(parser);
	// define_token_cmd(parser);
}
