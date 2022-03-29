/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:30:47 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/29 22:25:02 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_echo(t_program *program)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (program->args[i] != NULL && ft_strncmp(program->args[i], "-n", 3) == 0)
	{
		i++;
		flag = 1;
	}
	while (program->args[i])
	{
		ft_putstr_fd(program->args[i], STDOUT_FILENO);
		if (program->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
		g_exit_status = 0;
	}
	if (flag != 1)
		ft_putchar_fd('\n', );
}
