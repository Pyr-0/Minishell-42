/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:37:30 by shaas             #+#    #+#             */
/*   Updated: 2022/04/28 20:19:01 by mrojas-e         ###   ########.fr       */
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
	signal(SIGINT, SIG_IGN);

}

void	signalhandler_heredoc(int sig)
{
	if (sig == SIGINT)
		printf("\e[31mWTF!!!\e[0m\n");
	close(STDIN_FILENO);
}

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
	signal(SIGINT,signalhandler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
