/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_non_inbuilt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:35:18 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 20:42:27 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd(int fds_to_use[2], char *cmd_path, t_exec_block *i_exec,
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
		dup2(fds_to_use[READ], STDIN_FILENO);
		dup2(fds_to_use[WRITE], STDOUT_FILENO);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(cmd_path, argv, envp);
		exit(EXIT_FAILURE);
	}
	free(argv);
	free_split(envp);
}

bool	handle_non_inbuilt(int fds_to_use[2], t_exec_block *i_exec,
							t_exec_block *exec_blocks, int *child_process_num)
{
	bool	last_cmd_is_executable;
	char	*cmd_path;

	last_cmd_is_executable = false;
	cmd_path = find_cmd_path(i_exec->cmd, exec_blocks);
	if (cmd_path != NULL)
	{
		if (i_exec->next == NULL)
			last_cmd_is_executable = true;
		(*child_process_num)++;
		execute_cmd(fds_to_use, cmd_path, i_exec, exec_blocks);
	}
	free(cmd_path);
	return (last_cmd_is_executable);
}
