/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 21:48:45 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor_fail_exit(t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

void	congfigure_fds(int pp[2], int fds_to_use[2],
						int tmp_in, t_exec_block *i_exec)
{
	if (i_exec->in_fd == STDIN_FILENO)
		fds_to_use[READ] = tmp_in;
	else
		fds_to_use[READ] = i_exec->in_fd;
	if (i_exec->next != NULL)
	{
		if (pipe(pp) == -1)
			executor_fail_exit(i_exec);
		if (i_exec->out_fd == STDOUT_FILENO)
			fds_to_use[WRITE] = pp[WRITE];
	}
	if (i_exec->out_fd != STDOUT_FILENO)
		fds_to_use[WRITE] = i_exec->out_fd;
	else if (i_exec->next == NULL)
		fds_to_use[WRITE] = STDOUT_FILENO;
}

void	prepare_for_next_loop(int *tmp_in, int pp[2])
{
	if (*tmp_in != STDIN_FILENO)
		close(*tmp_in);
	if (pp[WRITE] != -1)
	{
		close(pp[WRITE]);
		pp[WRITE] = -1;
	}
	*tmp_in = dup(pp[READ]);
	if (pp[READ] != -1)
	{
		close(pp[READ]);
		pp[READ] = -1;
	}
}

bool	executor_loop(t_exec_block *exec_blocks, int *child_process_num)
{
	t_exec_block	*i_exec;
	bool			last_cmd_is_executable;
	int				pp[2];
	int				fds_to_use[2];
	int				tmp_in;

	i_exec = exec_blocks;
	last_cmd_is_executable = false;
	tmp_in = STDIN_FILENO;
	pp[0] = -1;
	pp[1] = -1;
	while (i_exec != NULL)
	{
		congfigure_fds(pp, fds_to_use, tmp_in, i_exec);
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(fds_to_use, i_exec, exec_blocks);
		else if (i_exec->cmd != NULL)
			last_cmd_is_executable = handle_non_inbuilt(fds_to_use,
					i_exec, exec_blocks, child_process_num, tmp_in, pp);
		prepare_for_next_loop(&tmp_in, pp);
		i_exec = i_exec->next;
	}
	close(pp[READ]);
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
