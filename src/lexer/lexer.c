/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/02 14:53:01 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_check_for_tokens(t_lexer *lexer, t_lexer_block **iter,
				t_lexer_block *first)
{
	if (lexer_peek_string(lexer, "|"))
	{
		lexer_advance(lexer);
		*iter = add_lexer_block(*iter, first);
	}
	else if (lexer_peek_string(lexer, "<<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_HEREDOC,
				NULL, *iter, first));
	else if (lexer_peek_string(lexer, "<"))
		lexer_advance_with_token(lexer, add_token(TOKEN_INPUT_FILE,
				NULL, *iter, first));
	else if (lexer_peek_string(lexer, ">>"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_APPEND,
				NULL, *iter, first));
	else if (lexer_peek_string(lexer, ">"))
		lexer_advance_with_token(lexer, add_token(TOKEN_OUTPUT_REPLACE,
				NULL, *iter, first));
	else
		lexer_collect_id(lexer, first, *iter);
}

t_lexer_block	*lexer(t_lexer *lexer)
{
	t_lexer_block	*first;
	t_lexer_block	*iter;

	init_lexer(lexer);
	first = init_lexer_block(NULL, lexer->contents);
	iter = first;
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '\0')
			break ;
		lexer_check_for_tokens(lexer, &iter, first);
	}
	return (first);
}
