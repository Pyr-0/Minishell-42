/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:22:12 by shaas             #+#    #+#             */
/*   Updated: 2022/04/20 22:30:26 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_varname(char *env_str, t_env *first)
{
	char	*varname;
	char	*c;

	varname = ft_strdup("");
	if (varname == NULL)
		env_fail_exit(first);
	while (*env_str != '=' && *env_str != '\0')
	{
		c = env_get_current_char_as_string(*env_str, first);
		varname = ft_strjoin_free(varname, c);
		if (varname == NULL)
			env_fail_exit(first);
		env_str++;
	}
	return (varname);
}

char	*get_varvalue(char *env_str, t_env *first)
{
	char	*varvalue;
	char	*c;

	
	varvalue = ft_strdup("");
	if (varvalue == NULL)
		env_fail_exit(first);
	while (*env_str != '=' && *env_str != '\0')
		env_str++;
	if (*env_str != '\0')
	{
		env_str++;
		while (*env_str != '\0')
		{
			c = env_get_current_char_as_string(*env_str, first);
			varvalue = ft_strjoin_free(varvalue, c);
			if (varvalue == NULL)
				env_fail_exit(first);
			env_str++;
		}
	}
	return (varvalue);
}

t_env	*init_env_node(char *env_str, t_env *first)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		env_fail_exit(first);
	node->varname = get_varname(env_str, first);
	node->varvalue = get_varvalue(env_str, first);
	node->next = NULL;
	return (node);
}

t_env	*add_env_node(char *env_str, t_env *prev, t_env *first)
{
	prev->next = init_env_node(env_str, first);
	return (prev->next);
}

t_env	*init_env(char *envp[])
{
	t_env	*first;
	t_env	*env;
	int		i;

	i = 1;
	env = init_env_node(envp[0], NULL);
	first = env;
	while (envp[i] != NULL)
	{
		env = add_env_node(envp[i], env, first);
		i++;
	}
	return (first);
}
