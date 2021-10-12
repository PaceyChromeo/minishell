/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:11:48 by pacey             #+#    #+#             */
/*   Updated: 2021/10/12 18:28:00 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

typedef struct s_lexer
{
	char	c;
	int		index;
	char	*value;
}				t_lexer;

typedef struct s_token
{
	enum e_type
	{
		token_cmd = 1,
		token_id,
		token_string_sq,
		token_string_dq,
		token_env,
		token_file,
		token_sred_l,
		token_sred_r,
		token_dred_l,
		token_dred_r,
		token_lparen,
		token_rparen,
		token_eof,
	}	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

t_token		*init_token(int type, char *value);
t_token		*get_next_token(t_lexer	*lexer);
t_lexer		*init_lexer(char *value);
void		lexer_next_char(t_lexer *lexer);
t_token		*lexer_collect_id(t_lexer *lexer);
t_token		*lexer_collect_string(t_lexer *lexer);
t_token		*lexer_collect_env(t_lexer *lexer);

#endif