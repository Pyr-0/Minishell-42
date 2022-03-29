/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:15:09 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 15:17:43 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*this one is for whenever there's an error somewhere in the program and the 
already initialized env struct needs to be freed*/
void	free_env(void)
{
	t_env	*env;
	t_env	*free_env;

	env = *(get_env(NULL));
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

/*this one is for when there happens an error during the creation of the env struct*/
void	free_init_env(t_env *env)
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
	free_init_env(env);
	exit(EXIT_FAILURE);
}
