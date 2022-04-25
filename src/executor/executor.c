/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/25 22:56:45 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor_fail_exit(t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

void	execute_cmd(void)
{
	return ;
}

void	executor(t_exec_block *exec_blocks)
{
	t_exec_block	*i_exec;
	char			*cmd_path;

	i_exec = exec_blocks;
	cmd_path = NULL;
	while (i_exec != NULL)
	{
		free (cmd_path);
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(i_exec, exec_blocks);
		else if (i_exec->cmd != NULL)
		{
			cmd_path = find_cmd_path(i_exec->cmd, exec_blocks);
			if (cmd_path != NULL)
				execute_cmd();
		}
		i_exec = i_exec->next;
	}
	free_close_exec_blocks(exec_blocks);
}
