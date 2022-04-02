/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:24:56 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/02 14:56:46 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(int type, char *value, t_lexer_block *first)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		lexer_blocks_fail_exit(first);
	token->e_type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

int	add_token(int type, char *value, t_lexer_block *curr, t_lexer_block *first)
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

t_lexer_block	*init_lexer_block(t_lexer_block *first, char *block_contents)
{
	t_lexer_block	*lexer_block;

	lexer_block = malloc(sizeof(t_lexer_block));
	if (lexer_block == NULL)
		lexer_blocks_fail_exit(first);
	lexer_block->tokens = NULL;
	lexer_block->next = NULL;
	lexer_block->block_contents = block_contents;
	return (lexer_block);
}

t_lexer_block	*add_lexer_block(t_lexer_block *prev, t_lexer_block *first)
{
	t_lexer_block	*new;

	new = init_lexer_block(first, NULL);
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
