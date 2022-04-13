/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:30:47 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/13 20:08:11 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(t_exec_block *echo)
{
	int	flag;

	flag = 0;
	while (echo->arg != NULL && ft_strncmp(echo->arg->value,
			"-n", 3) == 0)
	{
		echo->arg = echo->arg->next;
		flag = 1;
	}
	printf("\n\e[45mECHO COMMAND\e[0m\n");//
	while (echo->arg)
	{
		ft_putstr_fd(echo->arg->value, echo->out_fd);
		if (echo->arg->next)
			ft_putchar_fd(' ', echo->out_fd);
		echo->arg = echo->arg->next;
	}
	if (flag != 1)
		ft_putchar_fd('\n', echo->out_fd);
	g_exit_status = 0;
}