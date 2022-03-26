/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:27:59 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/26 15:13:56 by shaas            ###   ########.fr       */
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
	{
		lexer_advance(lexer);
	}
}

bool	lexer_peek_string(t_lexer *lexer, char *str)
{
	size_t	strlen;

	strlen = ft_strlen(str);
	if (ft_strncmp(&lexer->contents[lexer->i], str, strlen) == 0)
		return (true);
	else
		return (false);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
