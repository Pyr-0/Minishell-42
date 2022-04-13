/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:06:29 by shaas             #+#    #+#             */
/*   Updated: 2022/04/14 01:11:03 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
