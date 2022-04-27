/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/27 21:49:41 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor_fail_exit(t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

char	**argv_creator(t_exec_block *i_exec, t_exec_block *exec_blocks)
{
	char	**argv;
	t_arg	*i_arg;
	int		argc;
	int		i;

	argc = 1;
	i_arg = i_exec->arg;
	while (i_arg != NULL)
	{
		argc++;
		i_arg = i_arg->next;
	}
	argv = malloc((argc + 1) * sizeof(char *));
	if (argv == NULL)
		executor_fail_exit(exec_blocks);
	argv[0] = i_exec->cmd;
	i = 0;
	i_arg = i_exec->arg;
	while (++i < argc)
	{
		argv[i] = i_arg->value;
		i_arg = i_arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	env_counter(void)
{
	t_env	*i_env;
	int		envc;

	i_env = *(get_env(NULL));
	envc = 0;
	while (i_env != NULL)
	{
		envc++;
		i_env = i_env->next;
	}
	return (envc);
}

char	*env_helper(t_env *curr_env, t_exec_block *exec_blocks)
{
	char	*curr_envp;
	char	*buf;

	curr_envp = ft_strjoin(curr_env->varname, "=");
	if (curr_envp == NULL)
		executor_fail_exit(exec_blocks);
	buf = curr_envp;
	curr_envp = ft_strjoin(curr_envp, curr_env->varvalue);
	free (buf);
	if (curr_envp == NULL)
		executor_fail_exit(exec_blocks);
	return (curr_envp);
}

char	**envp_creator(t_exec_block *exec_blocks)
{
	char	**envp;
	t_env	*env;
	int		envc;
	int		i;

	envc = env_counter();
	envp = malloc((envc + 1) * sizeof(char *));
	if (envp == NULL)
		executor_fail_exit(exec_blocks);
	i = 0;
	env = *(get_env(NULL));
	while (i < envc)
	{
		envp[i] = env_helper(env, exec_blocks);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

// int	*duplicate_fds(i_exec, exec_blocks)
// {
// 	int	std_fds[2];

// 	std_fds[PIPE_READ] = dup(STDIN_FILENO);
// 	if (std_fds[PIPE_READ] == -1)
// 		executor_fail_exit(exec_blocks);
// 	std_fds[PIPE_WRITE] = dup(STDOUT_FILENO);
// 	if (std_fds[PIPE_WRITE] == -1)
// 	{
// 		close(std_fds[PIPE_READ]);
// 		executor_fail_exit(exec_blocks);
// 	}
// 	dup2(i_exec->in_fd, STDIN_FILENO);
// 	if (std_fds[PIPE_WRITE] == -1)
// 	{
// 		close(std_fds[PIPE_READ]);
// 		executor_fail_exit(exec_blocks);
// 	}
// 	dup2(i_exec->out_fd, STDOUT_FILENO);
// }

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

void	execute_cmd(char *cmd_path, t_exec_block *i_exec, t_exec_block *exec_blocks)
{
	char	**argv;
	char	**envp;
	pid_t	pid;

	argv = argv_creator(i_exec, exec_blocks);
	envp = envp_creator(exec_blocks);
	pid = fork();
	if (pid == -1)
		executor_fail_exit(exec_blocks);
	if (pid == 0)
	{
		dup2(i_exec->in_fd, STDIN_FILENO);
		dup2(i_exec->out_fd, STDOUT_FILENO);
		execve(cmd_path, argv, envp);
		exit(EXIT_FAILURE);
	}
	close_fds(i_exec);
	free(argv);
	free_split(envp);
}

bool	executor_loop(t_exec_block *exec_blocks)
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
	bool			last_cmd_is_executable;
	int				exit_status;

	last_cmd_is_executable = executor_loop(exec_blocks);
	while (wait(&exit_status) != -1) ;
	if (last_cmd_is_executable == true)
		g_exit_status = exit_status;
	free_close_exec_blocks(exec_blocks);
}
