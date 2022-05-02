/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:51:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 18:58:37 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_pwd(int fds_to_use[2], t_exec_block *cmd_pwd)
{
	char	*cwd;

	(void)cmd_pwd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (handle_error(
				"\e[46m\e[1;91mMi[shell]in: pwd: no, this ain't right 🤥\e[0m\n",
				EXIT_STD_ERROR));
	else
	{
		ft_putstr_fd(cwd, fds_to_use[WRITE]);
		ft_putstr_fd("\n", fds_to_use[WRITE]);
		g_exit_status = 0;
	}
	free(cwd);
	return (false);
}
