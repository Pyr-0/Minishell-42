/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/20 21:09:27 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_lexer(t_lexer *lexer, char *contents)
{
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->line_len = ft_strlen(contents);
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	char	*s;
	char	*value;

	lexer_advance(lexer);
	value = malloc(sizeof(char));
	value[0] = '\0';

	while (lexer->c != '"')
	{
		if (lexer->c == '\0')
		{
			printf("closing gaensefuesschen not found :'(\n");
			break ;
		}
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + strlen(s) + 1) * sizeof(char));
		ft_strlcat(value, s, INT_MAX);
		free (s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_ID, value)); //still not implemented the string management
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*s;
	char	*value;

	value = malloc(sizeof(char));
	value[0] = '\0';
	while (ft_isalnum(lexer->c))
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
	if (lexer->c != '\0')
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

t_command_block	*init_command_block(void)
{
	t_command_block	*command_block;

	command_block = malloc(sizeof(t_command_block));
	if (command_block == NULL)
		return (NULL);
	command_block->tokens = NULL;
	command_block->next = NULL;
	return (command_block);
}

t_command_block	*add_command_block(t_command_block *prev)
{
	t_command_block *new;

	new = init_command_block();
	if (new == NULL)
		return ;
	if (prev != NULL)
		prev->next = new;
	return (new);
}

t_command_block	*lexer(t_lexer *lexer)
{
	t_command_block	*first;
	t_command_block	*iter;

	first = init_command_block();
	iter = first;
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '|')
		{
			lexer_advance(lexer);
			iter = add_command_block(iter);
		}
		else if (lexer->c == '<')
		{
			if (lexer->c == '<' && peek_char(lexer) == '<')
				return (lexer_advance_with_token(lexer, init_token(TOKEN_INPUT_HEREDOC,
									lexer_get_current_char_as_string(lexer))));
			else
				return (lexer_advance_with_token(lexer, init_token(TOKEN_INPUT_FILE,
								lexer_get_current_char_as_string(lexer))));
		}
		else if (lexer->c == '>')
		{
			if (lexer->c == '>' && peek_char(lexer) == '>')
				return (lexer_advance_with_token(lexer, init_token(TOKEN_OUTPUT_APPEND,
									lexer_get_current_char_as_string(lexer))));
			else
				return (lexer_advance_with_token(lexer, init_token(TOKEN_OUTPUT_REPLACE,
								lexer_get_current_char_as_string(lexer))));
		}
		
/* 		else if (ft_strncmp(collect_fromstr(lexer), ">>", INT_MAX))
			return (lexer_advance_with_token(lexer, init_token(TOKEN_INPUT_HEREDOC,
					lexer_get_current_char_as_string(lexer))));
		else if (ft_strncmp(collect_fromstr(lexer), "<<", INT_MAX))
			return (lexer_advance_with_token(lexer, init_token(TOKEN_OUTPUT_APPEND,
					lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '<')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_OUTPUT_REPLACE,
								lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '>')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_INPUT_FILE,
								lexer_get_current_char_as_string(lexer)))); */
		else
		return (lexer_collect_id(lexer));
	}
	return (NULL);
}
