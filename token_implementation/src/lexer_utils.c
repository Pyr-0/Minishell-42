/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:27:59 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/22 21:49:13 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


bool	is_seperator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0')
		return (true);
	return (false);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
	{
		lexer_advance(lexer);
	}
}

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