/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advance_and_collect.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:54:08 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 15:07:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lexer_collect_string(t_lexer *lexer, t_command_block *first)
{
	char	*str;
	char	*c;
	char	quote_type;

	quote_type = lexer->c;
	str = ft_strdup("");
	if (str == NULL)
		command_blocks_fail_exit(first);
	while (true)
	{
		c = lexer_get_current_char_as_string(lexer, first);
		str = ft_strjoin_free(str, c);
		if (str == NULL)
			command_blocks_fail_exit(first);
		if (lexer->c == quote_type && ft_strlen(str) != 1)
			break ;
		lexer_advance(lexer);
	}
	return (str);
}

void	lexer_collect_id(t_lexer *lexer, t_command_block *first, t_command_block *curr)
{
	char	*s;
	char	*value;

	value = ft_strdup("");
	if (value == NULL)
		command_blocks_fail_exit(first);
	while (!is_seperator(lexer->c))
	{
		if ((lexer->c == '"' || lexer->c == '\'') && lexer_quote_is_closed(lexer))
			s = lexer_collect_string(lexer, first);
		else
			s = lexer_get_current_char_as_string(lexer, first);
		lexer_advance(lexer);
		value = ft_strjoin_free(value, s);
		if (value == NULL)
			command_blocks_fail_exit(first);
	}
	add_token(TOKEN_ID, value, curr, first);
}

void	lexer_advance_with_token(t_lexer *lexer, int token_len)
{
	int i;

	i = 0;
	while (i < token_len)
	{
		lexer_advance(lexer);
		i++;
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
	{
		lexer_advance(lexer);
	}
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}
