/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <ochichep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:05:41 by pacey             #+#    #+#             */
/*   Updated: 2021/10/25 11:26:48 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minishell.h"
# include "parsing.h"

char	*prompt_color(void);
int		error_handler(t_tree *tree);
int		check_forbidden_char(char *line);
char	*display_prompt(void);
void	handler_signals(int sig);
void	handler_child(int sig);

void	rl_replace_line(const char *text, int clear_undo);

#endif
