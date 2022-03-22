/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/22 22:49:26 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//t_token	*lexer_collect_string(t_lexer *lexer)
//{
//	char	*s;
//	char	*value;
//
//	lexer_advance(lexer);
//	value = malloc(sizeof(char));
//	value[0] = '\0';
//
//	while (lexer->c != '"')
//	{
//		if (lexer->c == '\0')
//		{
//			printf("closing gaensefuesschen not found :'(\n");
//			break ;
//		}
//		s = lexer_get_current_char_as_string(lexer);
//		value = ft_realloc(value, (ft_strlen(value) + strlen(s) + 1) * sizeof(char));
//		ft_strlcat(value, s, INT_MAX);
//		free (s);
//		lexer_advance(lexer);
//	}
//	lexer_advance(lexer);
//	return (init_token(TOKEN_ID, value)); //still not implemented the string management
//}

void	lexer_collect_id(t_lexer *lexer, t_command_block *first, t_command_block *curr)
{
	char	*s;
	char	*value;

	value = NULL;
	while (!is_seperator(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoin_free(value, s);
		lexer_advance(lexer);
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

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	check_for_tokens(t_lexer *lexer, t_command_block **iter, t_command_block *first)
{
	if (lexer_peek_string(lexer, "|"))
	{
		lexer_advance_with_token(lexer, add_token(TOKEN_PIPE, NULL, *iter, first));
		*iter = add_command_block(*iter, first);
	}
	else if (lexer_peek_string(lexer, "<<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_HEREDOC, NULL, *iter, first));
	else if (lexer_peek_string(lexer, "<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_FILE, NULL, *iter, first));
	else if (lexer_peek_string(lexer, ">>"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_APPEND, NULL, *iter, first));
	else if (lexer_peek_string(lexer, ">"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_REPLACE, NULL, *iter, first));
	else
		lexer_collect_id(lexer, first, *iter);
}

t_command_block	*lexer(t_lexer *lexer)
{
	t_command_block	*first;
	t_command_block	*iter;

	first = init_command_block(NULL);
	iter = first;
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '\0')
			break ;
		check_for_tokens(lexer, &iter, first);
	}
	return (first);
}
