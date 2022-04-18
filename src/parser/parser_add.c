/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:03:17 by shaas             #+#    #+#             */
/*   Updated: 2022/04/18 01:57:11 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_arg(t_parser_block *first, char *value,
				t_lexer_block *lexer_blocks, t_parser_block *curr)
{
	t_arg	*new;
	t_arg	*iter;

	new = init_arg(lexer_blocks, first);
	new->value = ft_strdup(value);
	if (new->value == NULL)
		parser_fail_exit(lexer_blocks, first);
	if (curr->arg == NULL)
		curr->arg = new;
	else
	{
		iter = curr->arg;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
}

t_redir	*add_redir(t_parser_block *curr, int redir_type,
				t_lexer_block *lexer_blocks, t_parser_block *first)
{
	t_redir	*new;
	t_redir	*iter;

	new = init_redir(lexer_blocks, first);
	new->e_redir_type = redir_type - 1;
	if (curr->redir == NULL)
		curr->redir = new;
	else
	{
		iter = curr->redir;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
	return (new);
}

void	add_cmd(t_parser_block *i_parser, t_token *i_token,
			t_parser_block *parser_blocks, t_lexer_block *lexer_blocks)
{
	i_parser->cmd = ft_strdup(i_token->value);
	if (i_parser->cmd == NULL)
		parser_fail_exit(lexer_blocks, parser_blocks);
}

void	add_redir_id(t_redir *new, t_token *i_token,
			t_parser_block *parser_blocks, t_lexer_block *lexer_blocks)
{
	new->id = ft_strdup(i_token->value);
	if (new->id == NULL)
		parser_fail_exit(lexer_blocks, parser_blocks);
}

t_parser_block	*add_parser_block(t_parser_block *first, t_parser_block *prev,
							t_lexer_block *lexer_blocks)
{
	t_parser_block	*new;

	new = init_parser_block(lexer_blocks, first);
	if (prev != NULL)
		prev->next = new;
	return (new);
}
