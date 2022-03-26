/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:24:56 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/26 15:13:56 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(int type, char *value, t_command_block *first)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		lexer_fail_exit(first);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

int	add_token(int type, char *value, t_command_block *curr, t_command_block *first)
{
	t_token	*last;
	int		token_len;

	if (type == TOKEN_INPUT_HEREDOC)
		token_len = 2;
	else if (type == TOKEN_INPUT_FILE)
		token_len = 1;
	else if (type == TOKEN_OUTPUT_REPLACE)
		token_len = 1;
	else if (type == TOKEN_OUTPUT_APPEND)
		token_len = 2;
	else
		token_len = 0;
	if (curr->tokens == NULL)
	{
		curr->tokens = init_token(type, value, first);
		return (token_len);
	}
	last = curr->tokens;
	while (last->next != NULL)
		last = last->next;
	last->next = init_token(type, value, first);
	return (token_len);
}

t_command_block	*init_command_block(t_command_block *first, char *block_contents)
{
	t_command_block	*command_block;

	command_block = malloc(sizeof(t_command_block));
	if (command_block == NULL)
		lexer_fail_exit(first);
	command_block->tokens = NULL;
	command_block->next = NULL;
	command_block->block_contents = block_contents;
	return (command_block);
}

t_command_block	*add_command_block(t_command_block *prev, t_command_block *first)
{
	t_command_block *new;

	new = init_command_block(first, NULL);
	if (prev != NULL)
		prev->next = new;
	return (new);
}

void	init_lexer(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->c = lexer->contents[lexer->i];
	lexer->line_len = ft_strlen(lexer->contents);
}
