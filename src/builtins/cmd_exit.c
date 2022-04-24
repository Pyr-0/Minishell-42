/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:40:29 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/24 19:14:57 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_exit(t_exec_block *cmd_exit)
{
	int	res;

	if (cmd_exit->arg == NULL)
		exit(g_exit_status);
	if (cmd_exit->arg->next != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		return (handle_error("\e[31mMi[shell]in:\
exit: toooo much too handle 😥\e[0m\n", EXIT_STD_ERROR));
	}
	if (ft_strchr(cmd_exit->arg->value, '+' ) != NULL || ft_strchr(cmd_exit->arg->value, '-') != NULL)
		cmd_exit->arg = cmd_exit->arg->next;
	if (cmd_exit->arg != NULL && ((ft_strcmp(cmd_exit->arg->value, "") == 0) || cmd_exit->arg->value != '\0' ))
	{
		if ((ft_strchr(cmd_exit->arg->value, '+' ) == NULL || ft_strchr(cmd_exit->arg->value, '-') == NULL)
				&& ft_isdigit(cmd_exit->arg->value[0]) != 1)
		{
			ft_putstr_fd("exit\n", 2);
			//free (cmd_exit);
			handle_error("\e[31mMi[shell]in:\
exit: give me numbers not words!\e[0m\n", EXIT_STD_ERROR);
			exit(255);
		}
		ft_atoi(cmd_exit->arg->value, &res);
		exit(res);
	}
	g_exit_status = EXIT_SUCCESS;
	return (0);
}
