/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:40:29 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 18:51:12 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_it_number(char *str)
{
	if (str == NULL)
		return (false);
	if (*str != '+' && *str != '-' && ft_isdigit(*str) == 0)
		return (false);
	str++;
	if (*str == '\0' && ft_isdigit(*(str - 1)) == 0)
		return (false);
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (false);
		str++;
	}
	return (true);
}

void	true_exit(int exit_status, t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(exit_status);
}

int	cmd_exit(t_exec_block *cmd_exit, t_exec_block *exec_blocks)
{
	int	res;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd_exit->arg == NULL)
		true_exit(g_exit_status, exec_blocks);
	if (cmd_exit->arg->next != NULL)
		return (handle_error("\e[46m\e[1;91mMi[shell]in: \
exit: toooo much too handle 😥\e[0m\n", EXIT_STD_ERROR));
	if (is_it_number(cmd_exit->arg->value) == false)
	{
		handle_error("\e[46m\e[1;91mMi[shell]in: \
exit: give me numbers not words!\e[0m\n", EXIT_STD_ERROR);
		true_exit(EXIT_INVALID_EXIT, exec_blocks);
	}
	ft_atoi(cmd_exit->arg->value, &res);
	if (ft_atoi(cmd_exit->arg->value, &res) == false
		|| res < 0 || res > 255)
		return (handle_error("\e[46m\e[1;91mMi[shell]in: \
exit: i think you have the wrong number 📞\e[0m\n", EXIT_STD_ERROR));
	true_exit(res, exec_blocks);
	return (0);
}
