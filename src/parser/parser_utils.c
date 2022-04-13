/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:31:35 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/14 01:39:31 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*translate_redir(t_token *i_token, t_parser_block *i_parser,
	t_lexer_block *lexer_blocks, t_parser_block *parser_blocks)
{
	t_redir	*new;

	new = add_redir(parser_blocks, i_token->e_type, lexer_blocks, i_parser);
	i_token = i_token->next;
	while (i_token != NULL && i_token->e_type == TOKEN_ID
		&& i_token->value[0] == '\0')
		i_token = i_token->next;
	if (i_token == NULL || i_token->e_type != TOKEN_ID)
	{
		handle_error_and_free(lexer_blocks, parser_blocks,
			"Ain't you an ambiguous one eh? 😏\n" );
		g_exit_status = EXIT_STD_ERROR;
		return (NULL);
	}
	add_redir_id(new, i_token, parser_blocks, lexer_blocks);
	return (i_token);
}
