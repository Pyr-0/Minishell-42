/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 12:59:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/20 19:29:57 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_env(t_exec_block *cmd_env)
{	
	t_env	*env;

	if (cmd_env->arg !=  NULL)
		return (handle_error(
			"Mi[shell]in: env: toooo much too handle\n",
			EXIT_STD_ERROR));//
	env = *(get_env(NULL));
	printf("\n\e[45mprint env start\e[0m\n");
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
	printf("\e[45mprint env end\e[0m\n\n");//
	g_exit_status = 0;
	return (false);
}
