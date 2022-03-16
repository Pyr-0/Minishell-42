/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/16 20:54:38 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	init_lexer(t_lexer *lexer, char *contents)
{
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->linelen = ft_strlen(contents);
}


t_token *lexer_collect_string(t_lexer *lexer)
{
	char *s;
	char *value;
	
	lexer_advance(lexer);
	value = malloc(sizeof(char));
	value[0] = '\0';
	
	while (lexer->c != '"')
	{
		if (lexer->c == '\0')
		{
			printf("closing gaensefuesschen not found :(\n");
			break ;
		}
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		ft_strlcat(value, s, INT_MAX);
		free (s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_STRING, value));
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char *lexer_get_current_char_as_string(t_lexer *lexer)
{
	char *str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';

	return (str);
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char *s;
	char *value;
	
	value = malloc(sizeof(char));
	value[0] = '\0';
	while (ft_isalnum(lexer->c)) // while current character is alphanumeric
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strlcat(value, s, INT_MAX);
		free (s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_ID, value));
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < lexer->linelen) // why both
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < lexer->linelen) //while we still have characters to parse we continue ;) // why both needed?
	{
		lexer_skip_whitespace(lexer);
		if (ft_isalnum(lexer->c))
			return (lexer_collect_id(lexer));
		else if (lexer->c == '"')
			return (lexer_collect_string(lexer));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_BIGGER,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SMALLER,
								lexer_get_current_char_as_string(lexer))));
		else
		{
			printf("wtf have you given me\n");
			break ;
		}
	}
	return (void *)0;
}
