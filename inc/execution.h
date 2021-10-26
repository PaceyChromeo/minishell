/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:59 by pacey             #+#    #+#             */
/*   Updated: 2021/10/26 15:17:11 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

typedef struct	t_env
{
	char			*var_env;
	struct t_env	*next;
}				lst_env;

typedef struct	s_var
{
	int		i;
	pid_t	pid;
	char	**env;
}				t_var;

/* FONCTIONS DE PIPES ET REDIRECTIONS */

void	exec_pipes(t_tree **cmds, char **env);
int		redirections(t_tree **cmds, int i);
int		right_redir(t_tree **cmds, int i, int j);
int		left_redir(t_tree **cmds, int i, int j);
void	loop_double_redir(t_tree **cmds, int i);
int		double_right_redir(t_tree **cmds, int i, int j);
int		double_left_redir(t_tree **cmds, int i, int j);

/* ---------------------------------- */

int		cmp_builtins(char *value);
int		builtins_cmd(t_tree *cmd);
int		cmp_binaries(char *value);
char	*get_path(char *cmd);
int		echo(t_tree *tree);
int		cd(char *path);
int		pwd(void);
int		export (char **args,char **env);
int		echo_option(char **args, int i);

/*FONCTION POUR LISTE CHAINER EXPORT */
int	len_list(lst_env *lst);
void free_list(lst_env *lst);
lst_env	*empty_list(void);
int	is_empty_list(lst_env *lst);
lst_env	*add_at(lst_env *lst, char *str, int pos);
void	set_at(lst_env *lst, char *str, int pos);
/***********************************/
/*FONCTIONS NECESSAIRE POUR LE BUILTIN EXPORT*/
char *ft_strstr(char *str, char *to_find); 
void print_list(lst_env *lst); /*AFFICHE LA LISTE CHAINER DONNER */
char *add_quote(char *arg); /*AJOUTE LES DOUBLES QUOTES DANS LES VARIABLE ENV*/
lst_env *push_env_to_list(char **env); /* ENVOYER LE CONTENU DE ENV DANS UNE LISTE CHAINER*/
lst_env	*add_at_push_to_env(lst_env *lst, char *str, int pos); /* MEME FONCTION QUE ADD_AT MAIS POUR PUSH_ENV_TO_LIST */
void add_var_last(lst_env **lst, char *str, int export); /* AJOUTE UNE STR A LA DERNIER POSITION DE LA LISTE*/
int	check_if_done(lst_env *lst); /*VERIFIE SI LA LISTE CHAINER ET TRIER*/
void sort_env_var(lst_env **lst); /* TRIER ENV PAR ORDRE ALPHABETIQUE */
void add_new(lst_env **lst, char *new_content, char *var_dest); /* AJOUTER UNE NOUVELLE VARIABLE AVEC SONT CONTENU */
char *add_content_to_var(char *dest, char *content_to_add);
int check_export_args_tab(char **arg); /* VERIFIER SI LES ARGUMENT ENVOYER SONT VALIDE */
int count_quotes(char *str); /*COMPTE LES QUOTES */
int count_equals(char *str); /* COMPTE LES EGALES */
int check_export_args_str(char *str); /* VERIFIE L ARGUMENT  */
int count_tab_nbr(char **args); /* donne la taille de d un tableau de 2 dimension */ 
int check_if_arg_in_env(char *var_name, lst_env *d_env);
int strlen_var_arg(char *str);
int ft_strstr_int(char *str, char *to_find);
#endif