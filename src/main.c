/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/29 14:58:36 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	get_env(envp);

	print_env();
	while (true)
	{
		printf("g_exit_status: %d\n\n", g_exit_status);
		lexer_struct.contents = readline("mi[SHELL]in$ ");
		if (lexer_struct.contents == NULL)
			exit_readline_fail();
		add_history(lexer_struct.contents);
		printf("Readline input is: %s\n", lexer_struct.contents);
		printf("System command exec:\n");
		system(lexer_struct.contents);
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