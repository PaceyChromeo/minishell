/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:53:12 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/14 17:23:51 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// printf("tree[%d] with cmd_type : %d\nsize_args : %d size_red : %d\n", y, root[y]->cmd_type, root[y]->size_args, root[y]->size_red);
					// t_lexer     *lexer = init_lexer(split[0]);
					// t_parser    *parser = init_parser(lexer);
					// while (parser->current_tok->type != token_eof)
					// {
					// 	printf("token type : %d | token value : %s\n", parser->current_tok->type, parser->current_tok->value);
					// 	parser_next_token(parser, parser->current_tok->type);
					// }
					// printf("----------------------------\n");
					// parser_define_more_token(parser);
					// parser->current_tok = parser->first_tok;
					// while (parser->current_tok->type != token_eof)
					// {
					// 	printf("token type : %d | token value : %s\n", parser->current_tok->type, parser->current_tok->value);
					// 	parser->current_tok = parser->current_tok->next;
					// }
					
void print_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		printf("[ %s ]", strs[i]);
		i++;
	}
}

void	print_tree(t_tree **root)
{
	int i;

	i = 0;
	while (root[i] != NULL)
	{
		printf("\nNumero de commande : [ \033[31m%d\033[0m ]\n", i + 1);
		printf("TYPE OF CMD = [ %d ] ARGS = ", root[i]->cmd_type);
		print_strs(root[i]->args);
		printf("\n");
		printf("REDIRECTIONS = ");
		print_strs(root[i]->red);
		printf("\nSIZE ARGS = [ %d ]\n", root[i]->size_args);
		printf("SIZE REDIR = [ %d ]\n", root[i]->size_red);
		i++;
	}
}