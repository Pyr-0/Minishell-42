/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:51:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/27 13:54:52 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_pwd(t_exec_block *cmd_pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (handle_error(
				"\e[46m\e[1;91mMi[shell]in: pwd: no, this ain't right 🤥\e[0m\n",
				EXIT_STD_ERROR));
	else
	{
		ft_putstr_fd(cwd, cmd_pwd->out_fd);
		ft_putstr_fd("\n", cmd_pwd->out_fd);
		g_exit_status = 0;
	}
	free(cwd);
	return (false);
}
