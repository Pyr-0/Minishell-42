/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:17:51 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 18:49:53 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_double_quotes(char **iter, char **new_token_value, t_lexer_block *first)
{
	(*iter)++;
	while (**iter != '"')
	{
		if (**iter == '$')
			expand_dollar_sign(iter, new_token_value, first);
		else
			expander_advance_with_char(iter, new_token_value, first);
	}
	(*iter)++;
}

void	expand_single_quotes(char **iter, char **new_token_value, t_lexer_block *first)
{
	(*iter)++;
	while (**iter != '\'')
	{
		expander_advance_with_char(iter, new_token_value, first);
	}
	(*iter)++;
}