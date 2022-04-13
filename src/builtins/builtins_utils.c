/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:19 by satori            #+#    #+#             */
/*   Updated: 2022/04/13 19:04:18 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fetch_env_var_value(char *varname)
{
	t_env *env;
	t_env *iter;

	env = *get_env(NULL);
	iter = env;

	while (iter != NULL)
	{
		if (ft_strncmp(iter->varname, varname, INT_MAX) == 0)
			return (iter->varvalue);
		iter = iter->next;
	}
	return (NULL);
}

bool	handle_error(char *msg, int exit_status)
{
	printf("%s", msg);
	g_exit_status = exit_status;
	return (true);
}
