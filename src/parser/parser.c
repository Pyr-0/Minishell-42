/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:46:50 by shaas             #+#    #+#             */
/*   Updated: 2022/03/30 22:50:48 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//to do: all pointer

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
}

// t_parser_block	*init_parser_block(t_lexer_block *lexer_blocks, t_parser_block *first)
// {
// 	t_parser_block	*parser_block;

// 	parser_block = malloc(sizeof(t_parser_block));
// 	if (parser_block == NULL)
// 		parser_fail_exit(lexer_blocks, first);
// 	parser_block-> = NULL;
// 	parser_block->next = NULL;
// 	parser_block->block_contents = block_contents;
// 	return (parser_block);
// }



