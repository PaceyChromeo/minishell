/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:05:41 by pacey             #+#    #+#             */
/*   Updated: 2021/10/18 15:55:34 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minishell.h"
# include "parsing.h"

char	*prompt_color(void);
int		error_handler(t_tree *tree);
int		check_forbidden_char(char *line);
int		treat_single_cmd(char *line, char **envp);
int		treat_multi_cmd(char *line, int cmd_nbr, char **envp);
char	*display_prompt(void);

#endif