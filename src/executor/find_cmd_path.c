/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:53:59 by shaas             #+#    #+#             */
/*   Updated: 2022/04/27 14:08:21 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("\e[46m\e[1;91mmi[SHELL]in: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": i know many commands,\
but this ain't one of 'em, babe 😌\e[0m", STDERR_FILENO);
	g_exit_status = EXIT_CMD_NOT_FOUND;
	return (NULL);
}

char	**prepare_paths(t_exec_block *exec_blocks)
{
	char	*path;
	char	**paths_split;
	char	*buf;
	int		i;

	path = fetch_env_var_value("PATH");
	if (path == NULL)
		return (NULL);
	paths_split = ft_split(path, ':');
	if (paths_split == NULL)
		executor_fail_exit(exec_blocks);
	i = 0;
	while (paths_split[i] != NULL)
	{
		if (*(ft_strrchr(paths_split[i], '/') + 1) != '\0')
		{
			buf = ft_strjoin(paths_split[i], "/");
			if (buf == NULL)
				executor_fail_exit(exec_blocks);
			free (paths_split[i]);
			paths_split[i] = buf;
		}
		i++;
	}
	return (paths_split);
}

char	**combine_paths_and_cmd(char *cmd, char **paths,
				t_exec_block *exec_blocks)
{
	int		i;
	char	*combined;

	i = 0;
	while (paths[i] != NULL)
	{
		combined = ft_strjoin(paths[i], cmd);
		if (combined == NULL)
			executor_fail_exit(exec_blocks);
		free (paths[i]);
		paths[i] = combined;
		i++;
	}
	return (paths);
}

char	*check_paths(char **paths, t_exec_block *exec_blocks)
{
	char	*working_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0)
		{
			working_path = ft_strdup(paths[i]);
			if (working_path == NULL)
				executor_fail_exit(exec_blocks);
			return (working_path);
		}
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_exec_block *exec_blocks)
{
	char	**paths;
	char	*cmd_path;

	if (access(cmd, X_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		if (cmd_path == NULL)
			executor_fail_exit(exec_blocks);
		return (cmd_path);
	}
	paths = prepare_paths(exec_blocks);
	if (paths == NULL)
		return (error_cmd_not_found(cmd));
	paths = combine_paths_and_cmd(cmd, paths, exec_blocks);
	cmd_path = check_paths(paths, exec_blocks);
	if (cmd_path == NULL)
		error_cmd_not_found(cmd);
	free_split(paths);
	return (cmd_path);
}
