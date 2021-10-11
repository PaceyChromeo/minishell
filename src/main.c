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
		split = ft_split_pipe(line, '|');
		if (split != NULL)
		{
			add_history(line);
			if (split)
			{
				for (int i = 0; split[i]; i++)
					printf("split[%d] = %s\n", i, split[i]);
				t_lexer     *lexer = init_lexer(split[0]);
				t_parser    *parser = init_parser(lexer);
				while (parser->current_tok->type != token_eof)
				{
					printf("token type : %d | token value : %s\n", parser->current_tok->type, parser->current_tok->value);
					parser_next_token(parser, parser->current_tok->type);
				}
				printf("----------------------------\n");
				parser_define_more_token(parser);
				parser->current_tok = parser->first_tok;
				while (parser->current_tok->type != token_eof)
				{
					printf("token type : %d | token value : %s\n", parser->current_tok->type, parser->current_tok->value);
					parser->current_tok = parser->current_tok->next;
				}
			}
		}
	}
	return (0);
}
