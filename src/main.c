#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int	ok = 1;
	const char *line;
	char **split;
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
				int y = 0;
				t_tree **root;
				int	cmd_nbr = count_pipes(line, '|') + 2;
				root = ft_calloc(cmd_nbr, sizeof(t_tree));
				if (!root)
					exit (0);
				while (split[y])
				{
					root[y] = create_trees(split[y]);
					printf("tree[%d] with cmd_type : %d and name : %s\nsize_args : %d size_red : %d\n", y, root[y]->cmd_type, root[y]->cmd_value, root[y]->size_args, root[y]->size_red);
					for (int j = 0; root[y]->args[j]; j++)
						printf("args[%d] = %s\n", j, root[y]->args[j]);
					for (int x = 0; root[y]->red[x]; x++)
						printf("red[%d] = %s\n", x, root[y]->red[x]);
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
					y++;
				}
				root[y] = NULL;
			}
		}
	}
	return (0);
}
