/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:58:43 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/19 14:28:43 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(int type)
{
	t_tree	*new_tree;

	new_tree = ft_calloc(1, sizeof(t_tree));
	if (!new_tree)
		return (NULL);
	new_tree->cmd_type = type;
	new_tree->cmd_value = NULL;
	new_tree->args = NULL;
	new_tree->red = NULL;
	new_tree->size_args = 0;
	new_tree->size_red = 0;
	return (new_tree);
}

static void	get_args_and_red(t_tree *tree, t_parser *parser)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tree->size_args > 0)
		tree->args = ft_calloc(tree->size_args + 1, sizeof(char *));
	if (tree->size_red > 0)
		tree->red = ft_calloc(tree->size_red + 1, sizeof(char *));
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		if (parser->current_tok->type > 0 && parser->current_tok->type < 6)
		{
			tree->args[i] = ft_strdup(parser->current_tok->value);
			i++;
		}
		if (parser->current_tok->type > 5 && parser->current_tok->type < 11)
		{
			tree->red[j] = ft_strdup(parser->current_tok->value);
			j++;
		}
		parser->current_tok = parser->current_tok->next;
	}
	if (tree->size_args > 0)
		tree->args[i] = NULL;
	if (tree->size_red > 0)
		tree->red[j] = NULL;
}

static void	get_type_and_size(t_tree *tree, t_parser *parser)
{
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		if (parser->current_tok->type == token_cmd)
		{
			if (cmp_builtins(parser->current_tok->value) < 7)
				tree->cmd_type = cmp_builtins(parser->current_tok->value);
			else if (cmp_binaries(parser->current_tok->value))
				tree->cmd_type = tree_execve;
			tree->cmd_value = ft_strdup(parser->current_tok->value);
		}
		if (parser->current_tok->type > 0 && parser->current_tok->type < 6)
			tree->size_args++;
		if (parser->current_tok->type > 5 && parser->current_tok->type < 11)
			tree->size_red++;
		parser->current_tok = parser->current_tok->next;
	}
}

t_tree	*create_trees(char *cmd)
{
	t_tree		*tree;
	t_lexer		*lexer;
	t_parser	*parser;

	tree = init_tree(tree_nocmd);
	lexer = init_lexer(cmd);
	parser = init_parser(lexer);
	while (parser->current_tok->type != token_eof)
		parser_next_token(parser, parser->current_tok->type);
	parser_define_more_token(parser);
	parser_get_token_with_env(parser);
	get_type_and_size(tree, parser);
	get_args_and_red(tree, parser);
	free_parser(parser);
	free(lexer);
	return (tree);
}
