/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_structs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:49:25 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/02 15:03:16 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*init_arg(t_lexer_block *lexer_blocks, t_parser_block *first)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (new == NULL)
		parser_fail_exit(lexer_blocks, first);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

t_redir	*init_redir(t_lexer_block *lexer_blocks, t_parser_block *first)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (new == NULL)
		parser_fail_exit(lexer_blocks, first);
	new->e_redir_type = -1;
	new->id = NULL;
	new->next = NULL;
	return (new);
}

t_parser_block	*init_parser_block(t_lexer_block *lexer_blocks,
				t_parser_block *first)
{
	t_parser_block	*new;

	new = malloc(sizeof(t_parser_block));
	if (new == NULL)
		parser_fail_exit(lexer_blocks, first);
	new->cmd = NULL;
	new->arg = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}
