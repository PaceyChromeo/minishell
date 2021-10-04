#include <minishell.h>

char	**init_builtin_lst()
{
	char	**blti_lst;
	blti_lst = malloc(sizeof(char *) * 8);
	if (!blti_lst)
		return (NULL);
	blti_lst[0] = "echo";
	blti_lst[1] = "cd";
	blti_lst[2] = "pwd";
	blti_lst[3] = "export";
	blti_lst[4] = "unset";
	blti_lst[5] = "env";
	blti_lst[6] = "exit";
	blti_lst[7] = NULL;
	return (blti_lst);
}
