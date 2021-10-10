#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int		ok;
	char	*line;
	//int		pipe;
	//pid_t pid;
        //int	status;
	//char	c;
	t_command	*cmd;
	char		**split_pp;

	ok = 1;
	char *line;
	(void)argc;
	(void)argv;
        (void)envp;
    while (ok)
	{
		prompt_color();   
	
		line = readline("");
		if (line != NULL)
		{
			add_history(line);
			if (line)
			{
				t_lexer     *lexer = init_lexer(line);
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
