/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:59 by pacey             #+#    #+#             */
/*   Updated: 2021/10/18 11:30:57 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"


int		cmp_builtins(char *value);
int		cmp_binaries(char *value);
char	*get_path(char *cmd);
void	exec_pipes(t_tree **cmds, char **env);
void	redirections(t_tree **cmds, int i);
void	exec_echo(t_tree *tree, int fd);

#endif