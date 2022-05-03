/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:40:29 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/03 19:44:32 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_it_number(char *str)
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

static void	true_exit(int exit_status, t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(exit_status);
}

static bool	ft_return(bool is_bigger, char *long_long_max)
{
	free (long_long_max);
	return (is_bigger);
}

static bool	is_bigger_than_long_long_max(char *str)
{
	char	*long_long_max;
	char	*long_long_iter;

	if (*str == '-')
		long_long_max = ft_strdup("9223372036854775808");
	else
		long_long_max = ft_strdup("9223372036854775807");
	if (long_long_max == NULL)
		executor_fail_exit(NULL);
	if (*str == '+' || *str == '-')
		str++;
	if (ft_strlen(str) > 19)
		return (ft_return(true, long_long_max));
	if (ft_strlen(str) < 19)
		return (ft_return(false, long_long_max));
	long_long_iter = long_long_max;
	while (*str != '\0')
	{
		if (*str > *long_long_iter)
			return (ft_return(true, long_long_max));
		str++;
		long_long_iter++;
	}
	return (false);
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
	if (is_bigger_than_long_long_max(cmd_exit->arg->value) == true)
	{
		handle_error("\e[46m\e[1;91mMi[shell]in: \
exit: i think you have the wrong number 📞\e[0m\n", EXIT_STD_ERROR);
		true_exit(EXIT_INVALID_EXIT, exec_blocks);
	}
	ft_atoi(cmd_exit->arg->value, &res);
	true_exit(res, exec_blocks);
	return (0);
}
