/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:18:03 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/19 14:11:58 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**get_limiter(t_tree **cmds, int i)
{
	int j;
	char **limiter;

	j = -1;
	limiter = NULL;
	while (cmds[i]->red[++j])
	{
		printf("%s\n", cmds[i]->red[j + 1]);	
	}	
	return (limiter);
}

int	left_redir(t_tree **cmds, int i, int j)
{
	int	filein;

	filein = open(cmds[i]->red[j + 1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		return (0);
	}
	dup2(filein, 0);
	return (1);
}

int	double_left_redir(t_tree **cmds, int i, int j)
{
	//int temp;
	//char *line;
	char **limiter;
	(void)j;

	limiter = get_limiter(cmds, i);
	// temp = open("temp.txt", O_CREAT | O_WRONLY, 0777);
	// while (write(1, "heredoc> ", ft_strlen("heredoc> ")) 
	// 	&& get_next_line(0, &line) > 0 && (ft_strcmp(line, limiter) != 0))
	// {
	// 	write(temp, line, ft_strlen(line));
	// 	write(temp, "\n", 1);
	// }
	// free(line);
	
	//unlink("temp.txt");
	return (1);
}