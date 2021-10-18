/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:05:41 by pacey             #+#    #+#             */
/*   Updated: 2021/10/18 17:10:22 by pjacob           ###   ########.fr       */
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

#endif