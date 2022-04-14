/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/14 02:01:27 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_cd(t_exec_block *cd)
{
	int		res;
	char	s[255]; //

	printf("%s\n", getcwd(s, 100)); //
	res = 0;
	if (cd->arg == NULL)
		res = chdir(fetch_env_var_value("HOME"));
	else if (cd->arg->next != NULL)
		return (handle_error(
				"Mi[shell]in: cd: toooo much too handle\n",
				EXIT_STD_ERROR));
	else
		res = chdir(cd->arg->value);
	if (res == -1)
		return (handle_error(
				"Mi[shell]in: cd: something was weird :/\n",
				EXIT_STD_ERROR));
	printf("%s\n", getcwd(s, 100));
	g_exit_status = EXIT_SUCCESS;
	return (false);
}
