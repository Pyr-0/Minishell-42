/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:30:47 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/14 01:24:27 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(t_exec_block *echo)
{
	int		flag;
	t_arg	*i_arg;

	flag = 0;
	i_arg = echo->arg;
	while (i_arg != NULL && ft_strncmp(i_arg->value,
			"-n", 3) == 0)
	{
		i_arg = i_arg->next;
		flag = 1;
	}
	printf("\n\e[45mECHO COMMAND\e[0m\n");//
	while (i_arg)
	{
		ft_putstr_fd(i_arg->value, echo->out_fd);
		if (i_arg->next)
			ft_putchar_fd(' ', echo->out_fd);
		i_arg = i_arg->next;
	}
	if (flag != 1)
		ft_putchar_fd('\n', echo->out_fd);
	g_exit_status = 0;
}