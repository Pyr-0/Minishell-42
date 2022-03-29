/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:46:50 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 19:47:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser_block	*parser(t_lexer_block *lexer_blocks)
{
	
}

t_parser_block	*init_parser_block(t_lexer_block *lexer_blocks, t_parser_block *first)
{
	t_parser_block	*parser_block;

	parser_block = malloc(sizeof(t_parser_block));
	if (parser_block == NULL)
		parser_fail_exit(lexer_blocks, first);
	parser_block-> = NULL;
	parser_block->next = NULL;
	parser_block->block_contents = block_contents;
	return (parser_block);
}



