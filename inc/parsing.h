/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:17:23 by pacey             #+#    #+#             */
/*   Updated: 2021/10/29 16:12:18 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "lexing.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_tok;
	t_token	*prev_tok;
	t_token	*first_tok;
}				t_parser;

typedef struct s_tree
{
	enum	e_cmd_type
	{
		tree_echo = 0,
		tree_cd,
		tree_pwd,
		tree_export,
		tree_unset,
		tree_env,
		tree_exit,
		tree_exportargs,
		tree_execve,
		tree_path,
		tree_nocmd
	}		cmd_type;
	char	*cmd_value;
	char	*f_cmd;
	char	**args;
	char	**red;
	int		size_args;
	int		size_red;
	int		z;
	int		save;
}				t_tree;

int			count_pipes(char const *line, char c);
char		**ft_split_pipe(char *s, char c);
t_parser	*init_parser(t_lexer *lexer);
void		parser_next_token(t_parser *parser);
void		parser_define_more_token(t_parser *parser);
void		parser_get_token_with_env(t_parser *parser);
t_tree		*init_tree(int type, char *cmd);
t_tree		*create_trees(char *cmd);

#endif