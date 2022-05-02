/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:59:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 18:46:52 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_env(int fds_to_use[2], t_exec_block *cmd_env)
{	
	t_env	*env;

	if (cmd_env->arg != NULL)
		return (handle_error("\e[46m\e[1;91mMi[shell]in:\
env: toooo much too handle 😥\e[0m\n", EXIT_STD_ERROR));
	env = *(get_env(NULL));
	while (env != NULL)
	{
		if (env->varvalue != NULL)
		{
			ft_putstr_fd(env->varname, fds_to_use[WRITE]);
			ft_putstr_fd("=", fds_to_use[WRITE]);
			ft_putendl_fd(env->varvalue, fds_to_use[WRITE]);
		}
		env = env->next;
	}
	g_exit_status = 0;
	return (false);
}
