/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/28 22:23:32 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*---------------------------------------------------------------------------*/
/*-------------------------------FOR TESTING---------------------------------*/
void	print_tokens(t_command_block *lexer_done)
{
	t_command_block	*i_block;
	t_token			*i_token;

	i_block = lexer_done;
	printf("-----------------------\n");
	while (i_block != NULL)
	{
		printf("new command block:\n");
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			printf("token_type: %d, token_value: %s\n", i_token->e_type, i_token->value);
			i_token = i_token->next;
		}
		i_block = i_block->next;
	}
	printf("-----------------------\n");
}

void	print_env(void)
{
	t_env	*env;

	env = *(get_env(NULL));
	while (env != NULL)
	{
		printf("%s=%s\n", env->varname, env->varvalue);
		env = env->next;
	}
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void	exit_readline_fail(void)
{
	free_env();
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[], char *envp[])
{
	t_lexer			lexer_struct;
	t_command_block	*lexer_done;

	if (argc != 1)
		return (1);
	(void)argv;
	g_exit_status = EXIT_SUCCESS;
	get_env(envp); //env needs to be freed everywhere!!!!! + ERROR HADNDLING $? //lexer & parser & env get current char as string alloc problem // env as function
	while (true)
	{
		printf("g_ext_status: %d\n\n", g_exit_status);
		lexer_struct.contents = readline("mi[SHELL]in$ ");
		if (lexer_struct.contents == NULL)
			exit_readline_fail();
		add_history(lexer_struct.contents);
		printf("Readline input is: %s\n", lexer_struct.contents);
		printf("System command exec:\n");
		system(lexer_struct.contents);
		init_lexer(&lexer_struct);
		lexer_done = lexer(&lexer_struct);
		print_tokens(lexer_done);
		if (pipe_redir_error(lexer_done) == true) //need to remake to handle empty token! and implement in parser
		{
			continue;
		}
		parser_expander(lexer_done); // need to handle empty string in executor!!. also exit stattus of successsfull command needs to be 0
		print_tokens(lexer_done);
		free_command_blocks(lexer_done);
	//	system("leaks minishell");
	//	break ; // testing
	}
	free_env();//at the end
	return (0);
}

/*
docker run -ti -v $(PWD):/test memory-test:0.1 bash -c "cd /test/; make re && valgrind --leak-check=full ./minishell"
*/