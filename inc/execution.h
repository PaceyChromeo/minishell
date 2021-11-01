/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:59 by pacey             #+#    #+#             */
/*   Updated: 2021/11/01 12:13:59 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

typedef struct s_env
{
	char			*var_env;
	struct s_env	*next;
}				t_lenv;

typedef struct s_var
{
	int			i;
	pid_t		pid;
	t_lenv		*env;
	char		**envp;
}				t_var;

/* FONCTIONS DE PIPES ET REDIRECTIONS */
void	exec_pipes(t_tree **cmds, t_var *var);
int		redirections(t_tree **cmds, int i);
int		right_redir(t_tree **cmds, int i, int j);
int		left_redir(t_tree **cmds, int i, int j);
void	loop_double_redir(t_tree **cmds, int i);
int		double_right_redir(t_tree **cmds, int i, int j);
int		double_left_redir(t_tree **cmds, int i, int j);

/* ---------------------------------- */
int		cmp_builtins(char *value);
int		builtins_cmd(t_tree *cmd, t_var *var);
int		cmp_binaries(char *value);
char	*get_path(char *cmd);
int		echo(t_tree *tree);
int		cd(t_var *var, char *path);
int		pwd(void);
int		exec_export(t_tree *tree, t_var *var);
int		exec_env(t_tree *tree, t_var *var);
int		echo_option(char **args, int i);
int		builtins_redir(t_tree *cmd);
void	loop_double_redirs(t_tree *cmds);
int		open_heredoc_builtins(t_tree *cmd, int j);
int		double_left_redirs(t_tree *cmd, int j);
int		left_redirs(t_tree *cmd, int j);

/*FONCTION POUR LISTE CHAINEE EXPORT */
int		len_list(t_lenv *lst);
void	free_list(t_lenv *lst);
t_lenv	*empty_list(void);
int		is_empty_list(t_lenv *lst);
t_lenv	*add_at(t_lenv *lst, char *str, int pos);

/*FONCTIONS NECESSAIRE POUR LE BUILTIN EXPORT*/
char	*ft_strstr(char *str, char *to_find);
void	print_list(t_lenv *lst, int i);
char	*add_quote(char *arg);
t_lenv	*push_env_to_list(char **env);
t_lenv	*add_and_push_to_env(t_lenv *lst, char *str, int pos);
void	add_var_last(t_lenv **lst, char *str, int export);
int		check_if_done(t_lenv *lst);
void	sort_env_var(t_lenv **lst);
void	add_new(t_lenv **lst, char *new_content, char *var_dest);
char	*add_content_to_var(char *dest, char *content_to_add);
int		check_export_args_tab(char **arg);
int		count_quotes(char *str);
int		count_equals(char *str);
int		check_export_args_str(char *str);
int		count_tab_nbr(char **args);
int		check_if_arg_in_env(char *var_name, t_lenv *d_env);
int		strlen_var_arg(char *str);
int		ft_strstr_int(char *str, char *to_find);
t_lenv	*ft_lstdup(t_lenv *lst);

/* FONCTION POUR UNSET */
int		exec_unset(t_tree *tree, t_var *var);
t_lenv	*free_at(t_lenv **lst, int pos);
/* EXTENSION FUNCTIONS */
void	haroun_la_pute(t_var *var, char *prix);

#endif