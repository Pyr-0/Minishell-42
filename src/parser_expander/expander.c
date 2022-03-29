/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:10:46 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 18:27:01 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_token(t_token *token, t_command_block *first)
{
	char	*iter;
	char	*new_token_value;

	new_token_value = ft_strdup("");
	if (new_token_value == NULL)
		command_blocks_fail_exit(first);
	iter = token->value;
	while (*iter != '\0')
	{
		if (*iter == EXPAND_DOUBLE_QUOTE && expander_quote_is_closed(iter))
			expand_double_quotes(&iter, &new_token_value, first);
		else if (*iter == EXPAND_SINGLE_QUOTE && expander_quote_is_closed(iter))
			expand_single_quotes(&iter, &new_token_value, first);
		else if (*iter == EXPAND_DOLLAR_SIGN)
			expand_dollar_sign(&iter, &new_token_value, first);
		else
			expander_advance_with_char(&iter, &new_token_value, first);
	}
	expander_init_new_value(token, new_token_value);
}

void	expander(t_command_block *lexer)
{
	t_command_block	*i_block;
	t_token			*i_token;

	i_block = lexer;
	while (i_block != NULL)
	{
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			if (i_token->e_type == TOKEN_ID)
				expand_token(i_token, lexer);
			i_token = i_token->next;
		}
		i_block = i_block->next;
	}
}
