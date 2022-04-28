/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:37:30 by shaas             #+#    #+#             */
/*   Updated: 2022/04/28 18:56:40 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fuck_sigpipe(int sig)
{
	(void)sig;
	return ;
}

/* void	signalhandler_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
} */

static void	signalhandler_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_setter(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &terminal);
	signal(SIGINT, signalhandler_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

 void	set_signal_heredoc(void)
{
	struct termios	terminal;

	tcgetattr(0,&terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0,0,&terminal);
	signal(SIGINT,set_signal_heredoc);
}