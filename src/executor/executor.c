/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/26 22:22:22 by shaas            ###   ########.fr       */
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
	i = 1;
	i_arg = i_exec->arg;
	while (i < argc)
	{
		argv[i] = i_arg->value;
		i++;
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

void	execute_cmd(char *cmd_path, t_exec_block *i_exec, t_exec_block *exec_blocks)
{
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		status;

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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	free(argv);
	free_split(envp);
}

void	executor(t_exec_block *exec_blocks)
{
	t_exec_block	*i_exec;
	char			*cmd_path;

	i_exec = exec_blocks;
	cmd_path = NULL;
	while (i_exec != NULL)
	{
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(i_exec, exec_blocks);
		else if (i_exec->cmd != NULL)
		{
			cmd_path = find_cmd_path(i_exec->cmd, exec_blocks);
			if (cmd_path != NULL)
				execute_cmd(cmd_path, i_exec, exec_blocks);
			free(cmd_path);
		}
		i_exec = i_exec->next;
	}
	free_close_exec_blocks(exec_blocks);
}
