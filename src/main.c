/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/28 19:55:31 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_readline_fail(void)
{
	free_env();
	exit(EXIT_FAILURE);
}

void	minishell_setup(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
	{
		printf("\e[31mwhat is your problem?\
I don't take any arguments from you 🙄\e[0m\n");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	g_exit_status = EXIT_SUCCESS;
	clear_signals();
	sig_setter();
	get_env(envp);
/* 	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); */
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer			lexer_struct;
	t_lexer_block	*lexer_done;
	t_parser_block	*parser_done;
	t_exec_block	*exec_done;

	minishell_setup(argc, argv, envp);
	while (true)
	{
		lexer_struct.contents = readline("\e[4;35m\e[40m\e[1;93mmi[SHELL]in\e[0;95m_> \e[0m"); //ft_strdup("< yeah << here hello > yup > nope"); // readline("mi[SHELL]in$ ");
		if (lexer_struct.contents == NULL)
			exit_readline_fail();
		add_history(lexer_struct.contents);
		lexer_done = lexer(&lexer_struct);
		if (pipe_redir_error(lexer_done) == true)
			continue ;
		expander(lexer_done);
		parser_done = parser(lexer_done);
		if (parser_done == NULL)
			continue ;
		exec_done = redir_creator(parser_done);
		print_exec_blocks(exec_done); //
		executor(exec_done);
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