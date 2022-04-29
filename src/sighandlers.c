/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:37:30 by shaas             #+#    #+#             */
/*   Updated: 2022/04/29 17:41:16 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fuck_sigpipe(int sig)
{
	(void)sig;
	return ;
}

void	clear_signals(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
}

static void	signalhandler_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	rl_redisplay();
}

void	signalhandler_ctrl_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
	}
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");

}

void	set_signals(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(1, 0, &terminal);
	signal(SIGINT, signalhandler_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

 void	set_signal_heredoc(void)
{
	struct termios	terminal;

	tcgetattr(0,&terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0,0,&terminal);
	signal(SIGINT,signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/* void	exit_signal(void)
{
	t_exec_block	info;

	if (info.cmd == NULL)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "exit\n", 5);
		free_close_exec_blocks(&info);
		exit (g_exit_status);
	}
} */