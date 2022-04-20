/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:51:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/20 19:10:28 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_pwd(t_exec_block *cmd_pwd)
{
	char	*cwd;

	if (cmd_pwd->arg !=  NULL)
		return (handle_error(
			"Mi[shell]in: pwd: toooo much too handle\n",
			EXIT_STD_ERROR));
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (handle_error("Mi[shell]in: pwd: Error\n", 2));
	else
	{
		ft_putstr_fd(cwd, cmd_pwd->out_fd);
		ft_putstr_fd("\n", cmd_pwd->out_fd);
		g_exit_status = 0;
	}
	free(cwd);
	return (false);
}
