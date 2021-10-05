/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:45:43 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/05 16:09:55 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stddef.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	int					*single_q;
	int					*double_q;
	int					nb_sq;
	int					nb_dq;
	int					nb_pp;
	char				*command;
	char				**blti_lst;
	char				**cmd_split;
}				t_command;

typedef struct s_token
{
	enum
	{
		token_cmd,
		token_string,
		token_lparen,
		token_rparen,
		token_sred,
		token_dred,
		token_eof,
	}	e_type;
	char	*value;
}				t_token;

typedef	struct	s_lexer
{
	char	c;
	int		index;
	char	*value;
}				t_lexer;


/*		DISPLAY FUNCTIONS	*/
char		*prompt(char *invite);
int			prompt_color(void);

/*		EXECUTIONS FUNCTIONS	*/
char		**init_builtin_lst(void);

/*		LEXING FUNCTIONS		*/
t_token		*init_token(int type, char *value);
t_lexer		*init_lexer(char *value);
void		lexer_next_char(t_lexer *lexer);
char		*get_char_as_string(t_lexer *lexer);
t_token		*lexer_collect_cmd(t_lexer *lexer);
t_token		*lexer_collect_string(t_lexer *lexer);

/*		PARSING FUNCTIONS	*/
char		*clean_redirection(char *str);
char		*str_trim(char *str, char c);
char		**ft_split_pipe(char const *s, char c);
char		**ft_split_space(char *s, char c);
char		***final_split(char *s, char c);
int			check_quote(char *line);
char		*clean_quotes(char *str);

/*		UTILS FUNCTIONS		*/
char		**ft_split(char const *s, char c);
//char		**get_path();
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcat(char *dest, const char *src);
int			ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isalpha(char c);
void		ft_putstr_fd(char *str, int fd);
void		blue(void);
void		yellow(void);
void		reset(void);

#endif
