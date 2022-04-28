/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:59:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/28 18:43:25 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_env(t_exec_block *cmd_env)
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
			ft_putstr_fd(env->varname, cmd_env->out_fd);
			ft_putstr_fd("=", cmd_env->out_fd);
			ft_putendl_fd(env->varvalue, cmd_env->out_fd);
		}
		env = env->next;
	}
	g_exit_status = 0;
	return (false);
}
