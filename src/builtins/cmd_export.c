/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:02:58 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/20 22:27:56 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static bool print_export(t_exec_block *cmd_export)
{
	t_env	*export;

	export = *(get_env(NULL));
	while (export != NULL)
	{
		ft_putstr_fd("declare -x ", cmd_export->out_fd);
		ft_putstr_fd(export->varname, cmd_export->out_fd);
		if (export->varvalue != NULL)
		{
			ft_putstr_fd("=", cmd_export->out_fd);
			ft_putchar_fd('"', cmd_export->out_fd);
			ft_putstr_fd(export->varvalue, cmd_export->out_fd);
			ft_putendl_fd("\"", cmd_export->out_fd);
		}
		export = export->next;
	}
	return (false);
}


bool	export_variable(t_arg *var)
{
	t_env	**env;
	
	env = get_env(NULL);
	init_env_node(var->value, *env);
}
bool	cmd_export(t_exec_block *cmd_export)
{
	t_arg *iter;
	int	exit_status;

	exit_status = 0;
	if(cmd_export->arg == NULL)
		return (print_export(cmd_export));
	iter = cmd_export->arg;
	while(iter != NULL)
	{
		if(iter->value[0] == '=')
		{
			handle_error(
				"Mi[shell]in: export: Watcha' tryna' export here darlin' 👀!\n",
				0);
			exit_status = EXIT_STD_ERROR;
		}
		else
			export_variable(iter, cmd_export);
		iter = iter->next;
	}
	g_exit_status = exit_status;
	return (false);
}
