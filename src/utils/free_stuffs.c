/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuffs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:15 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 13:37:19 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_parser(t_parser *parser)
{
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_eof)
	{
		parser->first_tok =  parser->current_tok;
		parser->current_tok = parser->current_tok->next;
		if (parser->first_tok->type > 0 && parser->first_tok->type < 11)
			free(parser->first_tok->value);
		parser->first_tok->prev = NULL;
		parser->first_tok->next = NULL;
		free(parser->first_tok);
	}
	free(parser);
}

void	free_tree(t_tree *tree)
{
	if (tree->cmd_type >= 0 && tree->cmd_type <= 7)
		free(tree->cmd_value);
	if (tree->size_args)
		free(tree->args);
	if (tree->size_red)
		free(tree->red);
	free(tree);
}

void	free_trees(t_tree **root)
{
	int	i;

	i = 0;
	while (root[i])
	{
		free_tree(root[i]);
		i++;
	}
	free(root);
}
