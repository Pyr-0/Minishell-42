/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 22:09:10 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor_fail_exit(t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

void	congfigure_fds(t_temp_fds *temp, t_exec_block *i_exec)
{
	if (i_exec->in_fd == STDIN_FILENO)
		temp->fds_to_use[READ] = temp->tmp_in;
	else
		temp->fds_to_use[READ] = i_exec->in_fd;
	if (i_exec->next != NULL)
	{
		if (pipe(temp->pp) == -1)
			executor_fail_exit(i_exec);
		if (i_exec->out_fd == STDOUT_FILENO)
			temp->fds_to_use[WRITE] = temp->pp[WRITE];
	}
	if (i_exec->out_fd != STDOUT_FILENO)
		temp->fds_to_use[WRITE] = i_exec->out_fd;
	else if (i_exec->next == NULL)
		temp->fds_to_use[WRITE] = STDOUT_FILENO;
}

void	prepare_for_next_loop(t_temp_fds *temp)
{
	if (temp->tmp_in != STDIN_FILENO)
		close(temp->tmp_in);
	if (temp->pp[WRITE] != -1)
	{
		close(temp->pp[WRITE]);
		temp->pp[WRITE] = -1;
	}
	temp->tmp_in = dup(temp->pp[READ]);
	if (temp->pp[READ] != -1)
	{
		close(temp->pp[READ]);
		temp->pp[READ] = -1;
	}
}

bool	executor_loop(t_exec_block *exec_blocks, int *child_process_num)
{
	t_exec_block	*i_exec;
	bool			last_cmd_is_executable;
	t_temp_fds		temp;

	i_exec = exec_blocks;
	last_cmd_is_executable = false;
	temp.tmp_in = STDIN_FILENO;
	temp.pp[0] = -1;
	temp.pp[1] = -1;
	while (i_exec != NULL)
	{
		congfigure_fds(&temp, i_exec);
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(temp.fds_to_use, i_exec, exec_blocks);
		else if (i_exec->cmd != NULL)
			last_cmd_is_executable = handle_non_inbuilt(&temp,
					i_exec, exec_blocks, child_process_num);
		prepare_for_next_loop(&temp);
		i_exec = i_exec->next;
	}
	close(temp.pp[READ]);
	return (last_cmd_is_executable);
}

void	executor(t_exec_block *exec_blocks)
{
	bool	last_cmd_is_executable;
	int		exit_status;
	int		child_process_num;

	child_process_num = 0;
	last_cmd_is_executable = executor_loop(exec_blocks, &child_process_num);
	while (child_process_num > 0)
	{
		waitpid(0, &exit_status, 0);
		child_process_num--;
	}
	if (last_cmd_is_executable == true)
		g_exit_status = exit_status;
	free_close_exec_blocks(exec_blocks);
}
