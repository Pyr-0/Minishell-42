/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/29 18:00:42 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_cd(t_exec_block *cd)
{
	int		res;

	res = 0;
	if (cd->arg == NULL)
		res = chdir(fetch_env_var_value("HOME"));
	else if (cd->arg->next != NULL)
		return (handle_error(
				"	\e[1;91mMi[shell]in: cd: toooo much too handle 😥 \e[0m\n",
				EXIT_STD_ERROR));
	else
		res = chdir(cd->arg->value);
	if (res == -1)
		return (handle_error("\e[1;91mMi[shell]in: \
cd: whatcha' lookin' for here Darlin' 🤨\e[0m\n", EXIT_STD_ERROR));
	g_exit_status = EXIT_SUCCESS;
	return (false);
}
