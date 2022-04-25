/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inbuilt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:51:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/25 22:53:25 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_inbuilt(t_exec_block *i_exec)
{
	if (ft_strcmp(i_exec->cmd, "echo") == 0
		|| ft_strcmp(i_exec->cmd, "cd") == 0
		|| ft_strcmp(i_exec->cmd, "pwd") == 0
		|| ft_strcmp(i_exec->cmd, "export") == 0
		|| ft_strcmp(i_exec->cmd, "unset") == 0
		|| ft_strcmp(i_exec->cmd, "env") == 0
		|| ft_strcmp(i_exec->cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

void	handle_inbuilt(t_exec_block *i_exec, t_exec_block *exec_blocks)
{
	(void)exec_blocks;
	if (ft_strcmp(i_exec->cmd, "echo") == 0)
		cmd_echo(i_exec);
	else if (ft_strcmp(i_exec->cmd, "cd") == 0)
		cmd_cd(i_exec);
	else if (ft_strcmp(i_exec->cmd, "env") == 0)
		cmd_env(i_exec);
	else if (ft_strcmp(i_exec->cmd, "pwd") == 0)
		cmd_pwd(i_exec);
	else if (ft_strcmp(i_exec->cmd, "export") == 0)
		cmd_export(i_exec);
	else if (ft_strcmp(i_exec->cmd, "unset") == 0)
		cmd_unset(i_exec);
	else if (ft_strcmp(i_exec->cmd, "exit") == 0)
		cmd_exit(i_exec);
}
