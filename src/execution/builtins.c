#include <minishell.h>

static char	**init_builtin_lst(void)
{
	char	**blti_lst;
	blti_lst = ft_calloc(8, sizeof(char *));
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

int	cmp_builtins(char *value)
{
	int	i;
	char	**bltin_lst;

	bltin_lst = init_builtin_lst();
	i = 0;
	while (i < 7)
	{
		if (!strcmp(bltin_lst[i], value))
			return (1);
		i++;
	}
	return (0);
}
