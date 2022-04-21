/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:23:58 by shaas             #+#    #+#             */
/*   Updated: 2022/04/21 19:21:19 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_get_current_char_as_string(char c, t_env *first)
{
	char	*str;

	str = calloc(2, sizeof(char));
	if (str == NULL)
		env_fail_exit(first);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*fetch_env_var_value(char *varname)
{
	t_env	*env;
	t_env	*iter;

	env = *get_env(NULL);
	iter = env;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->varname, varname) == 0)
			return (iter->varvalue);
		iter = iter->next;
	}
	return (NULL);
}
