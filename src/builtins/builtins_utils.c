/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:19 by satori            #+#    #+#             */
/*   Updated: 2022/04/21 21:35:48 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fetch_env_var_value(char *varname)
{
	t_env	*env;
	t_env	*iter;

	env = *get_env(NULL);
	iter = env;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->varname, varname) == 0)
		{
			if (iter->varvalue == NULL)
				return (iter->varname);
			return (iter->varvalue);
		}
		iter = iter->next;
	}
	return (NULL);
}

bool	handle_error(char *msg, int exit_status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit_status = exit_status;
	return (true);
}

