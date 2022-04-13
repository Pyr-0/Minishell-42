/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/13 19:09:54 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_cd(t_parser_block *cmd)
{
	int	res;

	char s[255];//
	printf("%s\n", getcwd(s, 100));//
	res = 0;
	if (cmd->arg == NULL) 
		res = chdir(fetch_env_var_value("HOME"));
	else if(cmd->arg->next != NULL)
		return (handle_error(
			"Mi[shell]in: cd : toooo much too handle\n", 
			EXIT_STD_ERROR));
	else
		res = chdir(cmd->arg->value);
	if (res == -1)
		return (handle_error(
			"Mi[shell]in: cd: something was weird :/\n", 
			EXIT_STD_ERROR));
	printf("%s\n", getcwd(s, 100));
	g_exit_status = EXIT_SUCCESS;
	return (false);
}
