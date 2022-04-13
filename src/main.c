/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/14 01:05:09 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_readline_fail(void)
{
	free_env();
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer			lexer_struct;
	t_lexer_block	*lexer_done;
	t_parser_block	*parser_done;
	t_exec_block	*exec_done;

	if (argc != 1)
	{
		printf("what is your problem? i don't take any arguments from you 🙄\n");
		return (1);
	}
	(void)argv;
	g_exit_status = EXIT_SUCCESS;
	signal(SIGPIPE, fuck_sigpipe);
	get_env(envp);
	//print_env();
	while (true)
	{
		printf("g_exit_status: %d\n\n", g_exit_status); //
		lexer_struct.contents = readline("mi[SHELL]in$ "); // ft_strdup("hello echo me"); // readline("mi[SHELL]in$ ");
		if (lexer_struct.contents == NULL)
			exit_readline_fail();
		add_history(lexer_struct.contents);
		printf("Readline input is: %s\n", lexer_struct.contents); //
		printf("System command exec:\n"); //
		//system(lexer_struct.contents); //
		lexer_done = lexer(&lexer_struct);
		//print_lexer_blocks(lexer_done); //
		if (pipe_redir_error(lexer_done) == true) //need to remake to handle empty token! and implement in parser
			continue;
		expander(lexer_done); // need to handle empty string in executor!!. also exit status of successfull command needs to be 0
		print_lexer_blocks(lexer_done); //
		parser_done = parser(lexer_done);
		if (parser_done == NULL)
			continue;
		print_parser_blocks(parser_done); //
		//test(parser_done); //
		//cmd_cd(parser_done);
		exec_done = redir_creator(parser_done);
		print_exec_blocks(exec_done); //
		cmd_echo(exec_done);
		free_close_exec_blocks(exec_done);
	//	system("leaks minishell"); //
	//	break ; //
	}
	free_env();//at the end
	return (0);
}

/*
docker run -ti -v $(PWD):/test memory-test bash -c "cd /test/; make re && valgrind --leak-check=full --show-leak-kinds=all ./minishell"
("\e[43mhere?\e[0m\n");
*/