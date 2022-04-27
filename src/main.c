/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/27 18:28:15 by mrojas-e         ###   ########.fr       */
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
		printf("\e[31mwhat is your problem?\
I don't take any arguments from you 🙄\e[0m\n");
		return (1);
	}
	(void)argv;
	g_exit_status = EXIT_SUCCESS;
	sig_setter();
	signal(SIGPIPE, fuck_sigpipe);
	get_env(envp);
	//print_env();
	int i = 0;//
	while (true)
	{
		printf("g_exit_status: %d\n\n", g_exit_status); //
		lexer_struct.contents = readline("\e[4;35m\e[40m\e[1;93mmi[SHELL]in\e[0;95m_>\e[0m"); //ft_strdup("< yeah << here hello > yup > nope"); // readline("mi[SHELL]in$ ");
		if (lexer_struct.contents == NULL)
			exit_readline_fail();
		add_history(lexer_struct.contents);
		//printf("Readline input is: %s\n", lexer_struct.contents); //
		//printf("System command exec:\n"); //
		//system(lexer_struct.contents); //
		lexer_done = lexer(&lexer_struct);
		print_lexer_blocks(lexer_done); //
		if (pipe_redir_error(lexer_done) == true)
			continue;
		expander(lexer_done); // need to handle empty string in executor!!. also exit status of successfull command needs to be 0
		print_lexer_blocks(lexer_done); //
		parser_done = parser(lexer_done);
		if (parser_done == NULL)
			continue;
		print_parser_blocks(parser_done); //
		exec_done = redir_creator(parser_done);
		print_exec_blocks(exec_done); //
		executor(exec_done);
		i++; //
	/* 	char *buf = malloc(1);
		while (true)
		{
			read(exec_done->in_fd, buf, 1);
			write(STDOUT_FILENO, buf, 1);
		} 
		free(buf);*/
	//	system("leaks minishell"); //
	//	free_env(); //at the end
	//	break ; //
	}
	return (0);
}

/*
(bash init_docker.sh)
(docker build -t memory-test .)
docker run -ti -v $(PWD):/test memory-test bash -c "cd /test/; make re && valgrind --leak-check=full --show-leak-kinds=all ./minishell"
lsof -c minishell
valgrind --leak-check=full --show-leak-kinds=all ./minishell 
printf("\e[43mhere?\e[0m\n");
*/