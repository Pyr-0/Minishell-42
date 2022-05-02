/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:30:47 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 20:45:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_echo(int fds_to_use[2], t_exec_block *echo)
{
	int		flag;
	t_arg	*i_arg;

	flag = 0;
	i_arg = echo->arg;
	while (i_arg != NULL && ft_strcmp(i_arg->value, "-n") == 0)
	{
		i_arg = i_arg->next;
		flag = 1;
	}
	while (i_arg)
	{
		ft_putstr_fd(i_arg->value, fds_to_use[WRITE]);
		if (i_arg->next)
			ft_putchar_fd(' ', fds_to_use[WRITE]);
		i_arg = i_arg->next;
	}
	if (flag != 1)
		ft_putchar_fd('\n', fds_to_use[WRITE]);
	g_exit_status = 0;
	return (false);
}
