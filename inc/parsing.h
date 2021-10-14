/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:15:46 by pacey             #+#    #+#             */
/*   Updated: 2021/10/14 15:28:33 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_tok;
	t_token	*prev_tok;
	t_token	*first_tok;
	ssize_t	token_size;
}				t_parser;

typedef struct s_tree
{
	enum	e_cmd_type
	{
		tree_nocmd = -1,
		tree_echo,
		tree_cd,
		tree_pwd,
		tree_export,
		tree_unset,
		tree_env,
		tree_exit,
	}		cmd_type;
	char	**args;
	char	**red;
	int		size_args;
	int		size_red;
}				t_tree;

int			count_pipes(char const *line, char c);
char		**ft_split_pipe(char const *s, char c);
t_parser	*init_parser(t_lexer *lexer);
void		parser_next_token(t_parser *parser, int type);
void		parser_define_more_token(t_parser *parser);
t_tree		*init_tree(int type);
t_tree		*create_trees(char *cmd);

#endif