/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuffs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:15 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/19 14:18:30 by pjacob           ###   ########.fr       */
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

void	free_token(t_token *token)
{
	if (token->type > 0 && token->type < 11)
		free(token->value);
	token->next = NULL;
	token->prev = NULL;
	free(token);
}

void	free_parser(t_parser *parser)
{
	parser->current_tok = parser->first_tok;
	while (parser->current_tok)
	{
		parser->first_tok = parser->current_tok;
		parser->current_tok = parser->current_tok->next;
		free_token(parser->first_tok);
	}
	free(parser);
}

void	free_tree(t_tree *tree)
{
	if (tree->cmd_type >= 0 && tree->cmd_type <= 7)
		free(tree->cmd_value);
	if (tree->size_args)
		free_tab(tree->args);
	if (tree->size_red)
		free_tab(tree->red);
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
