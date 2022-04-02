/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:12:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/02 14:42:35 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*this function initializes the env structure, when you pass it
	the env pointer from the main. in any other case, you should
	pass it NULL and it will just return the env structure.*/

t_env	**get_env(char *envp[])
{
	static t_env	*env;

	if (envp != NULL)
		env = init_env(envp);
	return (&env);
}
