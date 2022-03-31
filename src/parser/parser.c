/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:46:50 by shaas             #+#    #+#             */
/*   Updated: 2022/04/01 00:21:19 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//to do: all pointer

/*
t_parser_block	*parser(t_lexer_block *lexer_blocks)
{
	(void)lexer_blocks;

	t_parser_block	*parsi = malloc(sizeof(t_parser_block));

	parsi->cmd =  ft_strdup("go to hell");

	parsi->arg = malloc(sizeof(t_arg));
	parsi->arg->value = ft_strdup("--fuck");
	parsi->arg->next = malloc(sizeof(t_arg));
	parsi->arg->next->value = ft_strdup("--you");
	parsi->arg->next->next = NULL;

	parsi->input = malloc(sizeof(t_redir));
	parsi->input->e_redir_type = REDIR_INPUT_FILE;
	parsi->input->id = ft_strdup("from heaven");
	parsi->input->next = malloc(sizeof(t_redir));
	parsi->input->next->e_redir_type = REDIR_INPUT_HEREDOC;
	parsi->input->next->id = ft_strdup("stop when dead");
	parsi->input->next->next = NULL;

	parsi->output = malloc(sizeof(t_redir));
	parsi->output->e_redir_type = REDIR_OUTPUT_REPLACE;
	parsi->output->id = ft_strdup("to hell");
	parsi->output->next = malloc(sizeof(t_redir));
	parsi->output->next->e_redir_type = REDIR_OUTPUT_APPEND;
	parsi->output->next->id = ft_strdup("and back");
	parsi->output->next->next = NULL;

	parsi->next = malloc(sizeof(t_parser_block));
	parsi->next->cmd = NULL;
	parsi->next->arg = NULL;
	parsi->next->input = NULL;
	parsi->next->output = NULL;
	parsi->next->next = NULL;
	return (parsi);
}*/

t_parser_block	*init_parser_block(t_lexer_block *lexer_blocks, t_parser_block *first)
{
	t_parser_block *new;
	
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

t_parser_block	*add_parser_block(t_parser_block *first, t_parser_block *prev,
							t_lexer_block *lexer_blocks)
{
	t_parser_block *new;

	new = init_parser_block(lexer_blocks, first);
	if (prev != NULL)
		prev->next = new;
	return (new);
}

int	get_lexer_block_num(t_lexer_block *lexer_blocks)
{
	int	num;

	num = 0;
	while (lexer_blocks != NULL)
	{
		num++;
		lexer_blocks = lexer_blocks->next;
	}
	return (num);
}

t_parser_block	*parser(t_lexer_block *lexer_blocks)
{
	int	lexer_block_count;
	int	i;
	t_parser_block	*temp_block;
	t_parser_block	*first;

	i = 0;
	first = NULL;
	lexer_block_count = get_lexer_block_num(lexer_blocks);
	while(i < lexer_block_count)
	{
		temp_block = add_parser_block(first, temp_block, lexer_blocks);
		if (first == NULL)
			first = temp_block;
		i++;
	}
	return (first);
}