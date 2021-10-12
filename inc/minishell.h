/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:45:43 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/12 15:52:19 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stddef.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	enum e_type
	{
		token_cmd = 1,
		token_id = 2,
		token_string_sq = 3,
		token_string_dq = 4,
		token_env = 5,
		token_file = 6,
		token_sred_l = 7,
		token_sred_r = 8,
		token_dred_l = 9,
		token_dred_r = 10,
		token_lparen = 11,
		token_rparen = 12,
		token_eof = 13
	}	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef	struct	s_lexer
{
	char	c;
	int		index;
	char	*value;
}				t_lexer;

typedef struct	s_parser
{
	t_lexer	*lexer;
	t_token	*current_tok;
	t_token	*prev_tok;
	t_token *first_tok;
	ssize_t	token_size;
}				t_parser;

typedef struct	s_tree
{
	enum	e_cmd_type
	{
		tree_echo,
		tree_cd,
		tree_pwd,
		tree_export,
		tree_unset,
		tree_env,
		tree_exit,
		tree_nocmd,
	}	cmd_type;
	char	**args;
	char	**red;
	int		size_args;
	int		size_red;
}				t_tree;

/*		DISPLAY FUNCTIONS	*/
int			prompt_color(void);

/*		EXECUTIONS FUNCTIONS	*/
int			cmp_builtins(char *value);
int			cmp_binaries(char *value);
char		*get_path(char *cmd);

/*		LEXING FUNCTIONS		*/
t_token		*init_token(int type, char *value);
t_token		*get_next_token(t_lexer	*lexer);
t_lexer		*init_lexer(char *value);
void		lexer_next_char(t_lexer *lexer);
t_token		*lexer_collect_id(t_lexer *lexer);
t_token		*lexer_collect_string(t_lexer *lexer);
t_token		*lexer_collect_env(t_lexer *lexer);

/*		PARSING FUNCTIONS	*/
int			count_pipes(char const *line, char c);
char		**ft_split_pipe(char const *s, char c);
t_parser	*init_parser(t_lexer *lexer);
void		parser_next_token(t_parser *parser, int type);
void		parser_define_more_token(t_parser *parser);
t_tree		*init_tree(int type);
t_tree		*create_trees(char *cmd);

/*		UTILS FUNCTIONS		*/
void		free_tab(char **tab);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcat(char *dest, const char *src);
int			ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isalpha(char c);
void		ft_putstr_fd(char *str, int fd);
char		*ft_strcpy(char *cpy, char *src);
char		*ft_realloc_char(char *src, t_lexer *lexer);
void		*ft_calloc(int size, int type);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strdup(const char *s);
int			ft_is_ascii(char c);
void		blue(void);
void		yellow(void);
void		white(void);

#endif
