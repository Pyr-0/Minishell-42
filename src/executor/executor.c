/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/05/01 20:43:34 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor_fail_exit(t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

void	close_fds(t_exec_block *i_exec)
{
	if (i_exec->pp_in > STDERR_FILENO)
	{
		close(i_exec->pp_in);
		i_exec->pp_in = -1;
	}
	if (i_exec->in_fd > STDERR_FILENO)
	{
		close(i_exec->in_fd);
		i_exec->in_fd = -1;
	}
	if (i_exec->pp_out > STDERR_FILENO)
	{
		close(i_exec->pp_out);
		i_exec->pp_out = -1;
	}
	if (i_exec->out_fd > STDERR_FILENO)
	{
		close(i_exec->out_fd);
		i_exec->out_fd = -1;
	}
	if (i_exec->heredoc_pp_in > STDERR_FILENO)
	{
		close(i_exec->heredoc_pp_in);
		i_exec->heredoc_pp_in = -1;
	}
}

void	execute_cmd(char *cmd_path, t_exec_block *i_exec,
						t_exec_block *exec_blocks)
{
	char	**argv;
	char	**envp;
	pid_t	pid;

	argv = argv_creator(i_exec, exec_blocks);
	envp = envp_creator(exec_blocks);
	signal(SIGINT, signalhandler_ctrl_child);
	signal(SIGQUIT, signalhandler_ctrl_child);
	pid = fork();
	if (pid == -1)
		executor_fail_exit(exec_blocks);
	if (pid == 0)
	{
		dup2(i_exec->in_fd, STDIN_FILENO);
		dup2(i_exec->out_fd, STDOUT_FILENO);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(cmd_path, argv, envp);
		exit(EXIT_FAILURE);
	}
	close_fds(i_exec);
	free(argv);
	free_split(envp);
}

bool	executor_loop(t_exec_block *exec_blocks, int *child_process_num)
{
	t_exec_block	*i_exec;
	char			*cmd_path;
	bool			last_cmd_is_executable;

	cmd_path = NULL;
	i_exec = exec_blocks;
	last_cmd_is_executable = false;
	while (i_exec != NULL)
	{
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(i_exec, exec_blocks);
		else if (i_exec->cmd != NULL)
		{
			cmd_path = find_cmd_path(i_exec->cmd, exec_blocks);
			if (cmd_path != NULL)
			{
				if (i_exec->next == NULL)
					last_cmd_is_executable = true;
				(*child_process_num)++;
				execute_cmd(cmd_path, i_exec, exec_blocks);
			}
			free(cmd_path);
		}
		i_exec = i_exec->next;
	}
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
		waitpid(0, &exit_status, 0); // we must use waitpid in order to get exit status of last exec process
		child_process_num--;
	}
	if (last_cmd_is_executable == true)
		g_exit_status = exit_status;
	free_close_exec_blocks(exec_blocks);
}
