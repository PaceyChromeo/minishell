/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:18:26 by pacey             #+#    #+#             */
/*   Updated: 2021/10/26 12:27:56 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	print_token(t_token *token);
void	print_tree(t_tree *tree);
void	print_trees(t_tree **root);
void	free_tab(char **tab);
void	free_token(t_token *token);
void	free_parser(t_parser *parser);
void	free_tree(t_tree *tree);
void	free_all(t_tree **root, char **split, char *line);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalpha(char c);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strcpy(char *cpy, char *src);
char	*ft_realloc_char(char *src, char c);
void	*ft_calloc(int size, int type);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
int		ft_is_ascii(char c);
char	*ft_realloc(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
int		ft_isnum(char c);
int		ft_sch_forbidden_char(char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
void	ft_putnbr_fd(int n, int fd);
void	blue(void);
void	yellow(void);
void	white(void);
int		ft_atoi(const char *str);


#endif