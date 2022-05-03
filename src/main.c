/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/03 19:33:44 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_readline_fail(void)
{
	free_env();
	write(1, "exit\n", 6);
	exit(EXIT_FAILURE);
}

static void	minishell_setup(int argc, char *argv[], char *envp[])
{
	logo();
	if (argc != 1)
	{
		printf("\e[31mwhat is your problem?\
I don't take any arguments from you 🙄\e[0m\n");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	g_exit_status = EXIT_SUCCESS;
	get_env(envp);
}

static char	*ft_readline(void)
{
	char	*line;

	line = readline("\e[4;35m\e[40m\
\e[1;93mmi[SHELL]in\e[0;95m_> \e[0m");
	if (line == NULL)
		exit_readline_fail();
	add_history(line);
	return (line);
}

static void	reset_signals(void)
{
	clear_signals();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
		set_signals();
		lexer_struct.contents = ft_readline();
		lexer_done = lexer(&lexer_struct);
		if (pipe_redir_error(lexer_done) == true)
			continue ;
		expander(lexer_done);
		parser_done = parser(lexer_done);
		if (parser_done == NULL)
			continue ;
		exec_done = redir_creator(parser_done);
		if (exec_done == NULL)
			continue ;
		reset_signals();
		executor(exec_done);
	}
	return (0);
}
