/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:28 by hkrifa            #+#    #+#             */
/*                                                                            */

<<<<<<< HEAD
static int right_redirections(t_tree **cmds, int i, int j)
=======
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
>>>>>>> d5a36b1a314b4cef78edd5259714d2b04f3e39b6
{
	if (!ft_strcmp(cmds[i]->red[j], ">"))
		{
			if (!right_redir(cmds, i, j))
				return (0);
		}
		else if (!ft_strcmp(cmds[i]->red[j], ">>"))
		{
			if (!double_right_redir(cmds, i, j))
				return (0);
		}
		return (1);
}

static int left_redirections(t_tree **cmds, int i, int j)
{
	if (!ft_strcmp(cmds[i]->red[j], "<"))
		{
			if (!left_redir(cmds, i, j))
				return (0);
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<<"))
		{
			if (!double_left_redir(cmds, i, j))
			 	return (0);
		}
		return (1);
}

int	redirections(t_tree **cmds, int i)
{
	int	j;

	j = 0;
	while (cmds[i]->red[j] != NULL)
	{
<<<<<<< HEAD
		if (!ft_strcmp(cmds[i]->red[j], ">") 
			|| !ft_strcmp(cmds[i]->red[j], ">>"))
		{
			if (!right_redirections(cmds, i, j) )
=======
		if (!ft_strcmp(cmds[i]->red[j], ">"))
		{
			//printf(">\n");
			if (!right_redir(cmds, i, j))
<<<<<<< HEAD
				return (-1);
			return (0);
=======
		{
			if (!double_right_redir(cmds, i, j))
<<<<<<< HEAD
				return (-1);
			return (0);
=======
>>>>>>> d5a36b1a314b4cef78edd5259714d2b04f3e39b6
				return (0);
>>>>>>> 5f9ec7d54c14f37760abfd3c5197f5115d53cb2f
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<") 
			|| !ft_strcmp(cmds[i]->red[j], "<<"))
		{
<<<<<<< HEAD
			if (!left_redirections(cmds, i, j))
				return (0);
		}
=======
			if (!left_redir(cmds, i, j))
<<<<<<< HEAD
				return (-1);
			return (0);
=======
				return (0);
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<<"))
		{
			limiter = cmds[i]->red[j + 1];
			//printf("%s\n", limiter);
			 if (!double_left_redir(cmds, i, j))
			 	return (0);
>>>>>>> 5f9ec7d54c14f37760abfd3c5197f5115d53cb2f
		}
		// else if (!ft_strcmp(cmds[i]->red[j], "<<"))
		// {
		// 	limiter = cmds[i]->red[j + 1];
		// 	//printf("%s\n", limiter);
		// 	 if (!double_left_redir(cmds, i, j))
		// 	 	return (-1);
		// }
>>>>>>> d5a36b1a314b4cef78edd5259714d2b04f3e39b6
		j++;
	}
<<<<<<< HEAD
	return (0);
=======
	return (1);
>>>>>>> 5f9ec7d54c14f37760abfd3c5197f5115d53cb2f
}
