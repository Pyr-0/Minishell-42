/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:37:30 by shaas             #+#    #+#             */
/*   Updated: 2022/04/27 18:33:19 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fuck_sigpipe(int sig)
{
	(void)sig;
	return ;
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
	struct termios	mio;

	tcgetattr(0, &mio);
	mio.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &mio);
	signal(SIGINT, signalhandler_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
