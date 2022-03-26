/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:12:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/26 17:52:34 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_get_current_char_as_string(char c)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*get_varname(char *env_str)
{
	char	*varname;
	char	*c;

	varname = NULL;
	while (*env_str != '=' && *env_str != '\0')
	{
		c = env_get_current_char_as_string(*env_str);
		varname = ft_strjoin_free(varname, c);
		env_str++;
	}
	return (varname);
}

char	*get_varvalue(char *env_str)
{
	char	*varvalue;
	char	*c;

	varvalue = NULL;
	while (*env_str != '=' && *env_str != '\0')
		env_str++;
	if (*env_str != '\0')
	{
		env_str++;
		while (*env_str != '\0')
		{
			c = env_get_current_char_as_string(*env_str);
			varvalue = ft_strjoin_free(varvalue, c);
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
	node->varname = get_varname(env_str);
	node->varvalue = get_varvalue(env_str);
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

t_env	**get_env(char *envp[])
{
	static t_env	*env;

	if (envp != NULL)
		env = init_env(envp);
	return (&env);
}

void	free_env(t_env *env)
{
	t_env	*free_env;

	free_env = env;
	while (env != NULL)
	{
		free(env->varvalue);
		free(env->varname);
		free_env = env;
		env = env->next;
		free(free_env);
	}
}

void	env_fail_exit(t_env *env)
{
	free_env(env);
	exit(EXIT_FAILURE);
}
