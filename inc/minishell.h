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

typedef struct	s_command
{
	int					*single_q;
	int					*double_q;
	int					*pp_index;
	int					nb_sq;
	int					nb_dq;
	int					nb_pp;
	char				*command;
	char				**blti_lst;
	char				**cmd_split;
	struct	s_command	*last;
	struct	s_command	*next;
}				t_command;

typedef struct	s_cmd_list
{
	t_command	*first;
}				t_cmd_lst;

/*		DISPLAY FUNCTIONS	*/
char		*prompt(char *invite);
void		prompt_color();

/*		EXECUTIONS FUNCTIONS	*/
void		*init_builtin_lst(t_command *cmd);

/*		PARSING FUNCTIONS	*/
int			count_pipe(char *line, t_command *cmd);
char		*str_trim(char *str, char c);
char		lexer_quote(char *line);
t_command	*find_indexes(char *s);

/*		UTILS FUNCTIONS		*/
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcat(char *dest, const char *src);
void		ft_putstr_fd(char *str, int fd);
size_t		ft_strlen(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isalpha(char c);
void		blue(); 
void		yellow();
void		reset();
char		**get_path();
void		init_cmd_lst(t_cmd_lst *list, t_command *first);
int			count_lst(t_cmd_lst *list);
t_command	*last_cmd(t_cmd_lst	*list);
void		add_back(t_cmd_lst *list, t_command	*new);

#endif
