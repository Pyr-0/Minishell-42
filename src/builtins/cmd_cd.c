/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/03 19:43:58 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_cd(t_parser_block *cmd)
{
	int	res;
	char s[255];
	printf("%s\n", getcwd(s, 100));
	res = 0;
	if (cmd->arg)
	{
		res = chdir(cmd->arg->value);
		g_exit_status = 0;
	}
	if (res == -1)
	{
		g_exit_status = 2;
		perror("minishell: cd");
	}
	printf("%s\n", getcwd(s, 100));
}
