#include "minishell.h"

char    **get_path()
{
    char    **tab_path;
    char    *path;


    path = getenv("PATH");

    tab_path = ft_split(path, ':');
    return (tab_path);
}