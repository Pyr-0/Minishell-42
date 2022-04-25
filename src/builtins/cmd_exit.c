/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:40:29 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/25 21:30:54 by shaas            ###   ########.fr       */
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

int	cmd_exit(t_exec_block *cmd_exit)
{
	int	res;

	ft_putstr_fd("exit\n", 2);
	if (cmd_exit->arg == NULL)
		exit(g_exit_status);
	if (cmd_exit->arg->next != NULL)
		return (handle_error("\e[31mMi[shell]in: \
exit: toooo much too handle 😥\e[0m\n", EXIT_STD_ERROR));
	if (cmd_exit->arg != NULL && ft_strcmp(cmd_exit->arg->value, "") == 0)
	{
		if (is_it_number(cmd_exit->arg->value) == false)
		{
			handle_error("\e[31mMi[shell]in: \
exit: give me numbers not words!\e[0m\n", EXIT_STD_ERROR);
			exit(255);
		}
		ft_atoi(cmd_exit->arg->value, &res);
		if (ft_atoi(cmd_exit->arg->value, &res) == false || res < 0 || res > 255)
			return (handle_error("\e[31mMi[shell]in: \
exit: i think you have the wrong number 📞\e[0m\n", EXIT_STD_ERROR));
		exit(res);
	}
	return (0);
}
