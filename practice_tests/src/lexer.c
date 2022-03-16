/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/16 12:23:59 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer *lexer = calloc(1,sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];

	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) //while we still have characters to parse we continue ;)
	{
 		if (lexer->c == ' ' || lexer->c == 10) // 10 = '\n'. 
		lexer_skip_whitespace(lexer);
		if (isalnum(lexer->c))
			return (lexer_collect_id(lexer));
		if (lexer->c == '"')
			return (lexer_collect_string(lexer));
		if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_PIPE,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_BIGGER,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SMALLER,
								lexer_get_current_char_as_string(lexer))));
	}
	return (void *)0;
}

t_token *lexer_collect_string(t_lexer *lexer)
{
	char *s;
	char *value;
	
	lexer_advance(lexer);
	value = calloc(1 , sizeof(char));
	value[0] = '\0';
	
	while (lexer->c != '"')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value,s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);

	return (init_token(TOKEN_STRING, value));
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char *s;
	char *value;
	
	value = calloc(1,  sizeof(char));
	value[0] = '\0';
	
	while (isalnum(lexer->c)) // while current character is alphanumeric
	{
		s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value,s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_ID, value));
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

/*Replace the original with this values and use the asign token func to avoid leaks
 void	lexer_get_next_token(t_lexer *lexer, t_token *token)
t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) //while we still have characters to parse we continue ;)
	{
		if (lexer->c == ' ' || lexer->c == 10) // 10 = '\n'. 
			lexer_skip_whitespace(lexer);
		if (isalnum(lexer->c))
			return (lexer_collect_id(lexer));
		if (lexer->c == '"')
			return (lexer_collect_string(lexer));
		if (lexer->c == '=')
			return (lexer_advance_with_token(lexer, assign_token(token,TOKEN_EQUALS,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == ';')
			return (lexer_advance_with_token(lexer, assign_token(token,TOKEN_SEMI,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '(')
			return (lexer_advance_with_token(lexer, assign_token(token,TOKEN_PAR_LEFT,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == ')')
			return (lexer_advance_with_token(lexer, assign_token(token,TOKEN_PAR_RIGHT,
								lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, assign_token(token,TOKEN_BIGGER,
							lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, assign_token(token,TOKEN_SMALLER,
								lexer_get_current_char_as_string(lexer))));
	}
	return (void *)0;
}
 */