/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/22 13:24:32 by mrojas-e         ###   ########.fr       */
=======
/*   Updated: 2022/04/21 19:43:21 by shaas            ###   ########.fr       */
>>>>>>> 4f6bffb7ef9206d1aebfaef31d7ece5e99f2396f
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_cmd_path(char *cmd)
{
	char	*paths;
	char	**paths_split;
	int		i;

	if (access(cmd, ))
	paths = fetch_env_var_value("PATH");
	if (paths == NULL)
	{
		handle_error
	}
	paths_split = ft_split(paths, ':');
	i = 0;
	while(paths_split[i] != NULL)
	
}

void	executor(t_exec_block *exec_blocks)
{
	t_exec_block	*i_exec;
	char			*cmd_path;

	i_exec = exec_blocks;
	while (i_exec != NULL)
	{
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(i_exec);
<<<<<<< HEAD
=======
		else if (i_exec->cmd != NULL)
		{
			cmd_path = find_cmd_path(i_exec->cmd);
		}
>>>>>>> 4f6bffb7ef9206d1aebfaef31d7ece5e99f2396f
		i_exec = i_exec->next;
	}
	free_close_exec_blocks(exec_blocks);
}
