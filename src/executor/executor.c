/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:30:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/19 21:51:25 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_exec_block *exec_blocks)
{
	t_exec_block	*i_exec;

	i_exec = exec_blocks;
	while (i_exec != NULL)
	{
		if (is_inbuilt(i_exec) == true)
			handle_inbuilt(i_exec);	
		i_exec = i_exec->next;
	}
	free_close_exec_blocks(exec_blocks);
}
