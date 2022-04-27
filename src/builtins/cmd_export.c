/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:02:58 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/27 13:55:02 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	print_export(t_exec_block *cmd_export)
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
			ft_putchar_fd('"', cmd_export->out_fd);
		}
		ft_putchar_fd('\n', cmd_export->out_fd);
		export = export->next;
	}
	return (false);
}

void	replace_variable(char *varvalue, char *varname)
{
	t_env	**env;
	t_env	*iter;

	if (varvalue == NULL)
	{
		free (varname);
		return ;
	}
	env = get_env(NULL);
	iter = *env;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->varname, varname) == 0)
		{
			free (iter->varvalue);
			iter->varvalue = varvalue;
			free (varname);
			return ;
		}
		iter = iter->next;
	}
}

void	export_variable(t_arg *var)
{
	t_env	**env;
	t_env	*iter;
	char	*varname;
	char	*varvalue;

	env = get_env(NULL);
	varname = get_varname(var->value, *env);
	if (fetch_env_var_value(varname) != NULL)
	{
		varvalue = get_varvalue(var->value, *env);
		return (replace_variable(varvalue, varname));
	}
	free (varname);
	iter = *env;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = init_env_node(var->value, *env);
}

bool	cmd_export(t_exec_block *cmd_export)
{
	t_arg	*iter;
	int		exit_status;

	exit_status = 0;
	if (cmd_export->arg == NULL)
		return (print_export(cmd_export));
	iter = cmd_export->arg;
	while (iter != NULL)
	{
		if (iter->value[0] == '=')
		{
			handle_error("\e[46m\e[1;91mMi[shell]in: export: Watcha' tryna' \
export here darlin' 👀!\e[0m\n", 0);
			exit_status = EXIT_STD_ERROR;
		}
		else
			export_variable(iter);
		iter = iter->next;
	}
	g_exit_status = exit_status;
	if (exit_status == 0)
		return (false);
	else
		return (true);
}
