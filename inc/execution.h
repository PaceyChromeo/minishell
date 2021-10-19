/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:07:59 by pacey             #+#    #+#             */
/*   Updated: 2021/10/19 09:28:49 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"

typedef struct t_env
{
	char *var_env;
	struct t_env *next;
}	lst_env;


int		cmp_builtins(char *value);
void	bultins_cmd(t_tree *cmd);
int		cmp_binaries(char *value);
char	*get_path(char *cmd);
void	exec_pipes(t_tree **cmds, char **env);
int		redirections(t_tree **cmds, int i);
void	exec_echo(t_tree *tree, int fd);
void	echo(char **arg);
void	cd(char *path);
void	pwd(void);
void	export(char **args,char **env);

/*FONCTION POUR LISTE CHAINER EXPORT */

int		len_list(lst_env *lst);
lst_env	*free_list(lst_env *lst);
lst_env	*empty_list(void);
int		is_empty_list(lst_env *lst);
lst_env	*add_at(lst_env *lst, char *str, int pos);
<<<<<<< HEAD
/***********************************/
/*FONCTIONS NECESSAIRE POUR LE BUILTIN EXPORT*/
=======
lst_env	*push_env_to_list(char **env); /* ENVOYER LE CONTENU DE ENV DANS UNE LISTE CHAINER*/
void	add_var_last(lst_env **lst, char *str); /* AJOUTE UNE STR A LA DERNIER POSITION DE LA LISTE*/
int		check_if_done(lst_env *lst); /*VERIFIE SI LA LISTE CHAINER ET TRIER*/
lst_env	*sort_env_var(lst_env **lst); /* TRIER ENV PAR ORDRE ALPHABETIQUE */
char	*add_new(char *update, char *dest); /* AJOUTER UNE NOUVELLE VARIABLE AVEC SONT CONTENU */
lst_env	*update_var(lst_env **lst, char *var_name, char *update); /* METTRE A JOUR LE CONTENU D UNE VARIABLE DONNER */ 
int		check_export_args_tab(char **arg); /* VERIFIER SI LES ARGUMENT ENVOYER SONT VALIDE */
int		count_quotes(char *str);
int		count_equals(char *str);
int		check_export_args_str(char *str, int arg_pos);
int		count_tab_nbr(char **args);
int		echo_option(char *option);

#endif