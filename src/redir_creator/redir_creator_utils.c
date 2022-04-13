/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:29 by shaas             #+#    #+#             */
/*   Updated: 2022/04/14 01:27:31 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	redir_handler_fail(t_exec_block *i_exec)
{
	free(i_exec->cmd);
	i_exec->cmd = NULL;
	return (true);
}

void	replace_fd(int *old_fd, int new_fd)
{
	if (*old_fd > STDERR_FILENO)
		close (*old_fd);
	*old_fd = new_fd;
}

int	get_parser_block_num(t_parser_block *parser_blocks)
{
	int				num;
	t_parser_block	*iter;

	num = 0;
	iter = parser_blocks;
	while (iter != NULL)
	{
		num++;
		iter = iter->next;
	}
	return (num);
}
