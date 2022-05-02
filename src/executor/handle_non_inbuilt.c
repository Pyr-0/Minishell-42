/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_non_inbuilt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 20:35:18 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 22:21:40 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child(t_temp_fds *temp, char **argv, char **envp, char *cmd_path)
{
	dup2(temp->fds_to_use[READ], STDIN_FILENO);
	dup2(temp->fds_to_use[WRITE], STDOUT_FILENO);
	if (temp->tmp_in > STDERR_FILENO)
		close(temp->tmp_in);
	if (temp->pp[0] > STDERR_FILENO)
		close(temp->pp[0]);
	if (temp->pp[1] > STDERR_FILENO)
		close(temp->pp[1]);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (ft_strcmp(cmd_path, "./minishell") == 0)
	{
		ignore_all_signals(); // :(
		printf("%s\n", cmd_path); //
	}
	execve(cmd_path, argv, envp);
	exit(EXIT_FAILURE);
}

void	execute_cmd(t_temp_fds *temp, char *cmd_path, t_exec_block *i_exec,
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
		child(temp, argv, envp, cmd_path);
	}
	free(argv);
	free_split(envp);
}

bool	handle_non_inbuilt(t_temp_fds *temp, t_exec_block *i_exec,
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
		execute_cmd(temp, cmd_path, i_exec, exec_blocks);
	}
	free(cmd_path);
	return (last_cmd_is_executable);
}
