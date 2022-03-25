/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/25 22:07:37 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	print_tokens()

int main(int argc, char *argv[], char *envp[])
{
	t_env			*env;
	t_lexer			lexer_struct;
	t_command_block	*lexer_done = NULL;

	t_command_block	*i_block;
	t_token			*i_token;

	if (argc != 1)
		return (1);
	(void)argv;
	env = init_env(envp); //env needs to be freed everywhere!!!!! + ERROR HADNDLING $? //lexer & parser & env get current char as string alloc problem
	while(1)
	{
		lexer_struct.contents = readline("mi[SHELL]in$ ");
		printf("Readline input is:%s\n", lexer_struct.contents);
		printf("System command exec:\n");
		system(lexer_struct.contents);
		init_lexer(&lexer_struct);

		lexer_done = lexer(&lexer_struct);
		i_block = lexer_done;
		while (i_block != NULL)
		{
			printf("new command block:\n");
			i_token = i_block->tokens;
			while (i_token != NULL)
			{
				printf("token_type: %d, token_value: %s\n", i_token->type, i_token->value);
				i_token = i_token->next;
			}
			i_block = i_block->next;
		}
		if (pipe_redir_error(lexer_done) == true)
			continue;
		parser_expander(lexer_done, env);
		free_lexer(lexer_done);
		printf("\n");
	//	system("leaks minishell");
		// break ; // testing
	}
	return (0);
}

/*
docker run -ti -v $(PWD):/test memory-test:0.1 bash -c "cd /test/; make re && valgrind --leak-check=full ./minishell"
*/