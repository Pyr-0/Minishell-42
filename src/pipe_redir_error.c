/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:21:17 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/21 23:47:01 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	handle_error_and_free(t_lexer_block *lexer_block,
	t_parser_block *parser_blocks, char *error_message)
{
	free_lexer_blocks(lexer_block);
	free_parser_blocks(parser_blocks);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	g_exit_status = EXIT_PIPE_REDIR_ERROR;
	return (true);
}

bool	redir_error(t_token *token)
{
	if (token->e_type == TOKEN_ID)
		return (false);
	if (token->next == NULL || token->next->e_type != TOKEN_ID)
		return (true);
	return (false);
}

bool	pipe_error(t_lexer_block *block)
{
	if (block->next == NULL)
		return (false);
	if (block->tokens == NULL || block->next->tokens == NULL)
		return (true);
	return (false);
}

bool	pipe_redir_error(t_lexer_block *lexer_block)
{
	t_lexer_block	*i_block;
	t_token			*i_token;

	i_block = lexer_block;
	while (i_block != NULL)
	{
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			if (redir_error(i_token) == true)
				return (handle_error_and_free(lexer_block, NULL, "\
\e[31mEvery redirection needs an argument my dear 😌\e[0m\n"));
			i_token = i_token->next;
		}
		if (pipe_error(i_block) == true)
			return (handle_error_and_free(lexer_block, NULL,
					"\e[31mYou can't just pipe nothing 🤨\e[0m\n"));
		i_block = i_block->next;
	}
	return (false);
}
