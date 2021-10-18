/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:28 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 17:25:59 by pjacob           ###   ########.fr       */
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
		return (0);
	}
	if (cmds[i]->red[j + 2] == NULL)
	 	dup2(fileout, 1);
	return (1);
}

static int	double_right_redir(t_tree **cmds, int i, int j)
{
	int	fileout;

	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (0);
	}
	if (cmds[i]->red[j + 2] == NULL)
	 	dup2(fileout, 1);
	return (1);
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
	return (1);
}

// static int	double_left_redir(t_tree **cmds, int i, int j)
// {
// 	int temp;
// 	char *line;
// 	char *limiter;
// 	(void)i;
// 	(void)j;
// 	(void)cmds;
// 	temp = open("temp.txt", O_CREAT | O_WRONLY, 0777);
// 	while (write(1, "heredoc> ", ft_strlen("heredoc> ")) 
// 		&& get_next_line(0, &line) > 0 && (ft_strcmp(line, limiter) != 0))
// 	{
// 		write(temp, line, ft_strlen(line));
// 		write(temp, "\n", 1);
// 	}
// 	free(line);
	
// 	//unlink("temp.txt");
// 	return (1);
// }

int	redirections(t_tree **cmds, int i)
{
	int	j;
	//char *limiter;

	j = 0;
	while (cmds[i]->red[j] != NULL)
	{
		if (!ft_strcmp(cmds[i]->red[j], ">"))
		{
			//printf(">\n");
			if (!right_redir(cmds, i, j))
				return (-1);
			return (0);
		}
		else if (!ft_strcmp(cmds[i]->red[j], ">>"))
		{
			//printf(">>\n");
			if (!double_right_redir(cmds, i, j))
				return (-1);
			return (0);
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<"))
		{
			if (!left_redir(cmds, i, j))
				return (-1);
			return (0);
		}
		// else if (!ft_strcmp(cmds[i]->red[j], "<<"))
		// {
		// 	limiter = cmds[i]->red[j + 1];
		// 	//printf("%s\n", limiter);
		// 	 if (!double_left_redir(cmds, i, j))
		// 	 	return (-1);
		// }
		j++;
	}
	return (0);
}
