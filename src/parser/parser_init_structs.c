/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_structs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:49:25 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/01 21:06:47 by mrojas-e         ###   ########.fr       */
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

t_redir	*init_redir(t_lexer_block *lexer_blocks, t_parser_block *first)
{
	t_redir *new;
	
	new = malloc(sizeof(t_redir));
	if (new == NULL)
		parser_fail_exit(lexer_blocks, first);
	new->e_redir_type = -1;
	new->id = NULL;
	new->next = NULL;
	
	return (new);
}

void	add_redir(t_parser_block *first, int redir_type,
				t_lexer_block *lexer_blocks, t_parser_block *curr)
{
	t_redir	*new;
	t_redir	*iter;
	t_redir	**redir;

	if (redir_type <= TOKEN_INPUT_FILE)
		redir = &(curr->input);
	else
		redir = &(curr->output);
	new = init_redir(lexer_blocks, first);
	new->e_redir_type = redir_type - 1;
	if (*redir == NULL)
		*redir = new;
	else
	{
		iter = *redir;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
}

void	add_cmd(t_parser_block *i_parser, t_token *i_token,
			t_parser_block *parser_blocks, t_lexer_block *lexer_blocks)
{
	i_parser->cmd = ft_strdup(i_token->value);
	if (i_parser->cmd == NULL)
		parser_fail_exit(lexer_blocks, parser_blocks);
}

void	add_redir_id(t_parser_block *i_parser, t_token *i_token,
			t_parser_block *parser_blocks, t_lexer_block *lexer_blocks)
{
	t_redir *redir;

	if (i_token->e_type <= TOKEN_INPUT_FILE)
		redir = i_parser->input;
	else
		redir = i_parser->output;
	while (redir->next != NULL)
		redir = redir->next;
	redir->id = ft_strdup(i_token->next->value);
	if (redir->id == NULL)
		parser_fail_exit(lexer_blocks, parser_blocks);
}
