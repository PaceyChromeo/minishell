/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:28 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 16:45:20 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static int	right_redir(t_tree **cmds, int i, int j)
{	
	int	fileout;

	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (1);
	}
	if (cmds[i]->red[j + 2] == NULL)
	 	dup2(fileout, 1);
	return (fileout);
}

static int	double_right_redir(t_tree **cmds, int i, int j)
{
	int	fileout;

	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (1);
	}
	if (cmds[i]->red[j + 2] == NULL)
	 	dup2(fileout, 1);
	return (fileout);
}

static int	left_redir(t_tree **cmds, int i, int j)
{
	int	filein;

	filein = open(cmds[i]->red[j + 1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		return (0);
	}
	dup2(filein, 0);
	return (filein);
}

// static int	double_left_redir(t_tree **cmds, int i, int j)
// {
// 	int temp;
// 	char *line;

// 	temp = open("temp.txt", O_CREAT | O_WRONLY, 0777);
// 	while (write(1, "heredoc> ", ft_strlen("heredoc> ")) 
// 		&& get_next_line(0, &line) > 0 && (ft_strcmp(line, ) != 0))
// 	{
// 		write(temp, line, ft_strlen(line));
// 		write(temp, "\n", 1);
// 	}
// 	//unlink("temp.txt");
// 	return (1);
// }

int	redirections(t_tree **cmds, int i)
{
	int	j;
	int	fd;

	j = 0;
	while (cmds[i]->red[j] != NULL)
	{
		if (!ft_strcmp(cmds[i]->red[j], ">"))
		{
			//printf(">\n");
			fd = right_redir(cmds, i, j);
			if (fd == -1)
				return (-1);
			return (fd);
		}
		else if (!ft_strcmp(cmds[i]->red[j], ">>"))
		{
			//printf(">>\n");
			fd = double_right_redir(cmds, i, j);
			if (!fd)
				return (-1);
			return (fd);
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<"))
		{
			fd = left_redir(cmds, i, j);
			if (!fd)
				return (-1);
			return (fd);
		}
		// else if (!ft_strcmp(cmds[i]->red[j], "<<"))
		// {
		// 	printf("<<\n");
		// 	if (!double_left_redir(cmds, i, j))
		// 		return ;
		// }
		j++;
	}
	return (-1);
}
