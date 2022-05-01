/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 22:37:30 by shaas             #+#    #+#             */
/*   Updated: 2022/05/01 19:22:55 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
}

void	signalhandler_ctrlc(int sig)
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
	if (sig == SIGQUIT)
		write(1,"Quit: 3\n", 8);
}
