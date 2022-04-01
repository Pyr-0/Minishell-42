/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:46:50 by shaas             #+#    #+#             */
/*   Updated: 2022/04/01 22:53:50 by mrojas-e         ###   ########.fr       */
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


int	get_lexer_block_num(t_lexer_block *lexer_blocks)
{
	int				num;
	t_lexer_block	*iter;

	num = 0;
	iter = lexer_blocks;
	while (iter != NULL)
	{
		num++;
		iter = iter->next;
	}
	return (num);
}

t_parser_block	*create_parser_blocks(t_lexer_block *lexer_blocks)
{
	int	lexer_block_count;
	int	i;
	t_parser_block	*temp_block;
	t_parser_block	*first;

	i = 0;
	first = NULL;
	temp_block = first;
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

t_parser_block	*parser(t_lexer_block *lexer_blocks)
{
	t_parser_block	*parser_blocks;
	t_parser_block	*i_parser;
	t_lexer_block	*i_lexer;

	parser_blocks = create_parser_blocks(lexer_blocks);
	i_lexer = lexer_blocks;
	i_parser = parser_blocks;
	while(i_lexer != NULL && i_parser != NULL)
	{
		if (translate_lexer_to_parser_block(i_lexer, i_parser,
					lexer_blocks, parser_blocks) == false)
			return NULL;
		i_lexer = i_lexer->next;
		i_parser = i_parser->next;
	}
	free_lexer_blocks(lexer_blocks);
	return (parser_blocks);
}

bool	translate_lexer_to_parser_block(t_lexer_block *i_lexer,t_parser_block *i_parser,
								t_lexer_block *lexer_blocks, t_parser_block *parser_blocks)
{
	t_token	*i_token;

	i_token = i_lexer->tokens;
	while (i_token != NULL)
	{
		if (i_parser->cmd == NULL && i_token->e_type == TOKEN_ID)
			add_cmd(i_parser, i_token, parser_blocks, lexer_blocks);
		else if (i_parser->cmd != NULL && i_token->e_type == TOKEN_ID)
			add_arg(parser_blocks, i_token->value, lexer_blocks, i_parser);
		else if (i_token->e_type > TOKEN_ID)
		{
			add_redir(parser_blocks, i_token->e_type, lexer_blocks, i_parser);
			add_redir_id(i_parser, i_token, parser_blocks, lexer_blocks);
			i_token = i_token->next;
		}
		i_token = i_token->next;
	}
	return (true);
}
