/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:30:47 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/02 19:54:44 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(t_parser_block *echo)
{
	int	flag;

	flag = 0;
	while (echo->arg != NULL && ft_strncmp(echo->arg->value,
			"-n", 3) == 0)
	{
		echo->arg = echo->arg->next;
		flag = 1;
	}
	printf("\n\e[108mECHO COMMAND\e[0m\n");
	while (echo->arg)
	{
		ft_putstr_fd(echo->arg->value, STDOUT_FILENO);
		if (echo->arg->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		echo->arg = echo->arg->next;
	}
	if (flag != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_status = 0;
}
