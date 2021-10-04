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
	int					nb_sq;
	int					nb_dq;
	int					nb_pp;
	char				*command;
	char				**blti_lst;
	char				**cmd_split;
}				t_command;

/*		DISPLAY FUNCTIONS	*/
char		*prompt(char *invite);
int			prompt_color();

/*		EXECUTIONS FUNCTIONS	*/
char		**init_builtin_lst();
int			check_command(char *str);

/*		PARSING FUNCTIONS	*/
char		*clean_redirection(char *str);
char		*str_trim(char *str, char c);
char		**ft_split_pipe(char const *s, char c);
char		**ft_split_space(char *s, char c);
char 		***final_split(char *s, char c);
int			check_quote(char *line);
char		*clean_quotes(char *str);

/*		UTILS FUNCTIONS		*/
char		**ft_split(char const *s, char c);
//char		**get_path();
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcat(char *dest, const char *src);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_isalpha(char c);
void		ft_putstr_fd(char *str, int fd);
void		blue(); 
void		yellow();
void		reset();

#endif
