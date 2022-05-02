/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:02:58 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 18:59:48 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	print_export(int fds_to_use[2])
{
	t_env	*export;

	export = *(get_env(NULL));
	while (export != NULL)
	{
		ft_putstr_fd("declare -x ", fds_to_use[WRITE]);
		ft_putstr_fd(export->varname, fds_to_use[WRITE]);
		if (export->varvalue != NULL)
		{
			ft_putstr_fd("=", fds_to_use[WRITE]);
			ft_putchar_fd('"', fds_to_use[WRITE]);
			ft_putstr_fd(export->varvalue, fds_to_use[WRITE]);
			ft_putchar_fd('"', fds_to_use[WRITE]);
		}
		ft_putchar_fd('\n', fds_to_use[WRITE]);
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

bool	cmd_export(int fds_to_use[2], t_exec_block *cmd_export)
{
	t_arg	*iter;
	int		exit_status;

	exit_status = 0;
	if (cmd_export->arg == NULL)
		return (print_export(fds_to_use));
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
