/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:27:59 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/14 18:36:57 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_seperator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0')
		return (true);
	return (false);
}

bool	lexer_quote_is_closed(t_lexer *lexer)
{
	if (ft_strchr(&lexer->contents[lexer->i + 1], lexer->c) != NULL)
		return (true);
	return (false);
}

bool	lexer_peek_string(t_lexer *lexer, char *str)
{
	if (ft_strncmp(&lexer->contents[lexer->i], str, ft_strlen(str)) == 0)
		return (true);
	else
		return (false);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer, t_lexer_block *first)
{
	char	*str;

	str = calloc(2, sizeof(char));
	if (str == NULL)
		lexer_blocks_fail_exit(first);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
