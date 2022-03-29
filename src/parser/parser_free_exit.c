/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:22:09 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 19:44:25 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser_blocks(t_parser_block *parser_blocks)
{
	t_parser_block	*free_blocks;

	free_blocks = parser_blocks;
	while (parser_blocks != NULL)
	{
		parser_free_redir(parser_blocks->input);
		parser_free_redir(parser_blocks->output);
		parser_free_args(parser_blocks->arg);
		free(parser_blocks->cmd);
		parser_blocks = parser_blocks->next;
		free(free_blocks);
		free_blocks = parser_blocks;
	}
}

void	parser_fail_exit(t_lexer_block *lexer_blocks, t_parser_block *parser_blocks)
{
	free_lexer_blocks(lexer_blocks);
	free_parser_blocks(parser_blocks);
	exit (EXIT_FAILURE);
}


void	parser_free_redir(t_redir *redir)
{
	t_redir	*free_redir;

	free_redir = redir;
	while(redir != NULL)
	{
		free(redir->id);
		redir = redir->next;
		free(free_redir);
		free_redir = redir;
	}
}

void	parser_free_args(t_arg *args)
{
	t_arg	*free_args;

	free_args = args;
	while(args != NULL)
	{
		free(args->value);
		args = args->next;
		free(free_args);
		free_args = args;
	}
}