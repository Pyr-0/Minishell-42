/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:24:56 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/22 20:43:33 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	else if (TOKEN_OUTPUT_REPLACE)
		token_len = 1;
	else if (TOKEN_OUTPUT_APPEND)
		token_len = 2;
	else if (type == TOKEN_PIPE)
		token_len = 1;
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