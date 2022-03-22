/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/22 20:44:00 by mrojas-e         ###   ########.fr       */
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

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

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

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

t_command_block	*init_command_block(t_command_block *first)
{
	t_command_block	*command_block;

	command_block = malloc(sizeof(t_command_block));
	if (command_block == NULL)
		lexer_fail_exit(first);
	command_block->tokens = NULL;
	command_block->next = NULL;
	return (command_block);
}

t_command_block	*add_command_block(t_command_block *prev, t_command_block *first)
{
	t_command_block *new;

	new = init_command_block(first);
	if (prev != NULL)
		prev->next = new;
	return (new);
}

void	free_lexer(t_command_block *command_blocks)
{
	t_command_block	*free_blocks;
	t_token			*free_tokens;

	free_blocks = command_blocks;
	while (command_blocks != NULL)
	{
		while (command_blocks->tokens != NULL)
		{
			free_tokens = command_blocks->tokens;
			command_blocks->tokens = command_blocks->tokens->next;
			free(free_tokens->value);
			free(free_tokens);
		}
		free_blocks = command_blocks;
		command_blocks = command_blocks->next;
		free(free_blocks);
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

void	check_for_tokens(t_lexer *lexer, t_command_block *iter, t_command_block *first)
{
	if (lexer_peek_string(lexer, "|"))
	{
		lexer_advance_with_token(lexer, add_token(TOKEN_PIPE, NULL, iter, first));
		iter = add_command_block(iter, first);
	}
	else if (lexer_peek_string(lexer, "<<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_HEREDOC, NULL, iter, first));
	else if (lexer_peek_string(lexer, "<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_FILE, NULL, iter, first));
	else if (lexer_peek_string(lexer, ">>"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_APPEND, NULL, iter, first));
	else if (lexer_peek_string(lexer, ">"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_REPLACE, NULL, iter, first));
	else
		lexer_collect_id(lexer, first, iter);
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
		check_for_tokens(lexer, iter, first);
	}
	return (first);
}
