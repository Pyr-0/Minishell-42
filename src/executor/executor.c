/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/25 16:33:25 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor_fail_exit(t_exec_block *exec_blocks)
{
	free_close_exec_blocks(exec_blocks);
	free_env();
	exit(EXIT_FAILURE);
}

/* char	*find_cmd_path(char *cmd, t_exec_block *exec_blocks)
{
	char	*paths;
	char	**paths_split;
	char	*cmd_path;
	int		i;
	int		j;

	if (access(cmd, X_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		if (cmd_path == NULL)
			executor_fail_exit(exec_blocks);
		return (cmd_path);
	}
	paths = fetch_env_var_value("PATH");
	if (paths == NULL)
	{
		handle_error(""); // it think we don't need that, see what happens then. or maybe we should?
	}
	paths_split = ft_split(paths, ':');
	if (paths_split == NULL)
	{
		return (error_cmd_not_found(cmd));
	}
	i = 0;
	j = 0;
	while(paths_split[i] != NULL)
	{
		while (paths_split[i][j] != '\0')
			j++;
		if ()
		cmd_path = ft_strjoin()
	}
	
} */

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
			handle_inbuilt(i_exec);
/*  		else if (i_exec->cmd != NULL)
		{
			cmd_path = find_cmd_path(i_exec->cmd, exec_blocks);
		} */
		i_exec = i_exec->next;
	}
	free_close_exec_blocks(exec_blocks);
}
