/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:18:26 by pacey             #+#    #+#             */
/*   Updated: 2021/10/12 18:28:21 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_tab(char **tab);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalpha(char c);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strcpy(char *cpy, char *src);
char	*ft_realloc_char(char *src, t_lexer *lexer);
void	*ft_calloc(int size, int type);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
int		ft_is_ascii(char c);
void	blue(void);
void	yellow(void);
void	white(void);

#endif