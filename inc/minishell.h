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

/*		DISPLAY FUNCTIONS	*/

char	*prompt(char *invite);
void	prompt_color();

/*		EXECUTIONS FUNCTIONS	*/

/*		PARSING FUNCTIONS	*/
int		count_pipe(char *line);
char	*trim_str(char *s);

/*		UTILS FUNCTIONS		*/
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalpha(char c);
void	blue(); 
void	yellow();
void	reset();
char	**get_path();

#endif
