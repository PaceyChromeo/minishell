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

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
void	ft_putstr_fd(char *str, int fd);

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2); //le vrai

void    blue(); 
void    yellow();
void    reset();
 void   prompt_color();
char    *prompt(char *invite);

char    **get_path();
int     count_pipe(char *line);

#endif
