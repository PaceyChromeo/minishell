#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int	ok = 1;
	char *line = NULL;
	char **split = NULL;
	(void)argc;
	(void)argv;
    (void)envp;
    while (ok)
	{
		prompt_color();   
	
		line = readline("");
		add_history(line);
		split = ft_split_pipe(line, '|');
		if (split != NULL)
		{
			if (split)
			{
				// for (int i = 0; split[i]; i++)
				// 	printf("split[%d] = %s\n", i, split[i]);
				int i = 0;
				t_tree **root;
				int	cmd_nbr = count_pipes(line, '|') + 2;
				root = ft_calloc(cmd_nbr, sizeof(t_tree));
				if (!root)
					exit (0);
				while (split[i])
				{
					root[i] = create_trees(split[i]);
					printf("tree[%d] with cmd_type : %d\nsize_args : %d size_red : %d\n", i, root[i]->cmd_type, root[i]->size_args, root[i]->size_red);
					for (int j = 0; root[i]->args[j]; j++)
							printf("args[%d] = %s\n", j, root[i]->args[j]);
					for (int x = 0; root[i]->red[x]; x++)
							printf("red[%d] = %s\n", x, root[i]->red[x]);
					// t_lexer     *lexer = init_lexer(split[0]);
					// t_parser    *parser = init_parser(lexer);
					// while (parser->current_tok->type != token_eof)
					// {
					// 	printf("token type : %d | token value : %s\n", parser->current_tok->type, parser->current_tok->value);
					// 	parser_next_token(parser, parser->current_tok->type);
					// }
					// printf("----------------------------\n");
					// parser_define_more_token(parser);
					// parser->current_tok = parser->first_tok;
					// while (parser->current_tok->type != token_eof)
					// {
					// 	printf("token type : %d | token value : %s\n", parser->current_tok->type, parser->current_tok->value);
					// 	parser->current_tok = parser->current_tok->next;
					// }
					i++;
				}
			}
		}
	}
	return (0);
}
