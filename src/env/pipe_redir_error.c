/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:21:17 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/26 19:08:04 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_error_and_free(t_command_block *lexer_block, char *error_message)
{
	free_lexer(lexer_block);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (true);
}

bool	redir_error(t_token *token)
{
	if (token->type == TOKEN_ID)
		return (false);
	if (token->next == NULL || token->next->type != TOKEN_ID)
		return (true);
	return (false);
}

bool	pipe_error(t_command_block *block)
{
	if (block->next == NULL)
		return (false);
	if (block->tokens == NULL || block->next->tokens == NULL)
		return (true);
	return (false);
}

bool	pipe_redir_error(t_command_block *lexer_block)
{
	t_command_block	*i_block;
	t_token			*i_token;

	i_block = lexer_block;
	while (i_block != NULL)
	{
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			if (redir_error(i_token) == true)
					return (handle_error_and_free(lexer_block, "Every redirection needs an argument my dear 😌\n"));
			i_token = i_token->next;
		}
		if (pipe_error(i_block) == true)
			return (handle_error_and_free(lexer_block, "You can't just pipe nothing 🤨\n"));
		i_block = i_block->next;
	}
	return (false);
}
