/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 22:40:03 by shaas             #+#    #+#             */
/*   Updated: 2022/03/25 17:35:31 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lexer(t_command_block *command_blocks)
{
	t_command_block	*free_blocks;
	t_token			*free_tokens;

	free_blocks = command_blocks;
	while (command_blocks != NULL)
	{
		while (command_blocks->tokens != NULL)
		{
			free_tokens = command_blocks->tokens;
			command_blocks->tokens = command_blocks->tokens->next;
			free(free_tokens->value);
			free(free_tokens);
		}
		free(command_blocks->block_contents);
		free_blocks = command_blocks;
		command_blocks = command_blocks->next;
		free(free_blocks);
	}
}

void	lexer_fail_exit(t_command_block *command_blocks)
{
	free_lexer(command_blocks);
	exit(EXIT_FAILURE);
}
