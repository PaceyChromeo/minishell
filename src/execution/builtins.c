#include <minishell.h>

void	*init_builtin_lst(t_command *cmd)
{
	cmd->blti_lst = malloc(sizeof(char *) * 8);
	if (!cmd->blti_lst)
		return (NULL);
	cmd->blti_lst[0] = "echo";
	cmd->blti_lst[1] = "cd";
	cmd->blti_lst[2] = "pwd";
	cmd->blti_lst[3] = "export";
	cmd->blti_lst[4] = "unset";
	cmd->blti_lst[5] = "env";
	cmd->blti_lst[6] = "exit";
	cmd->blti_lst[7] = NULL;
	return (cmd);
}
