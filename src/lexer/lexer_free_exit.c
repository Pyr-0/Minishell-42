/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:40:03 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 18:49:53 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer_blocks(t_lexer_block *lexer_blocks)
{
	t_lexer_block	*free_blocks;
	t_token			*free_tokens;

	free_blocks = lexer_blocks;
	while (lexer_blocks != NULL)
	{
		while (lexer_blocks->tokens != NULL)
		{
			free_tokens = lexer_blocks->tokens;
			lexer_blocks->tokens = lexer_blocks->tokens->next;
			free(free_tokens->value);
			free(free_tokens);
		}
		free(lexer_blocks->block_contents);
		free_blocks = lexer_blocks;
		lexer_blocks = lexer_blocks->next;
		free(free_blocks);
	}
}

void	lexer_blocks_fail_exit(t_lexer_block *lexer_blocks)
{
	free_env();
	free_lexer_blocks(lexer_blocks);
	exit(EXIT_FAILURE);
}
