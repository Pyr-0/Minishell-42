/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:46:50 by shaas             #+#    #+#             */
/*   Updated: 2022/04/02 21:43:30 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int				lexer_block_count;
	int				i;
	t_parser_block	*temp_block;
	t_parser_block	*first;

	i = 0;
	first = NULL;
	temp_block = first;
	lexer_block_count = get_lexer_block_num(lexer_blocks);
	while (i < lexer_block_count)
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
	while (i_lexer != NULL && i_parser != NULL)
	{
		if (translate_lexer_to_parser_block(i_lexer, i_parser,
				lexer_blocks, parser_blocks) == true)
			return (NULL);
		i_lexer = i_lexer->next;
		i_parser = i_parser->next;
	}
	free_lexer_blocks(lexer_blocks);
	return (parser_blocks);
}

bool	translate_lexer_to_parser_block(t_lexer_block *i_lexer,
					t_parser_block *i_parser, t_lexer_block *lexer_blocks,
					t_parser_block *parser_blocks)
{
	t_token	*i_token;

	i_token = i_lexer->tokens;
	while (i_token != NULL)
	{
		if (i_token->e_type == TOKEN_ID && i_parser->cmd == NULL
			&& i_token->value[0] != '\0')
			add_cmd(i_parser, i_token, parser_blocks, lexer_blocks);
		else if (i_token->e_type == TOKEN_ID && i_parser->cmd != NULL
			&& i_token->value[0] != '\0')
			add_arg(parser_blocks, i_token->value, lexer_blocks, i_parser);
		else if (i_token->e_type > TOKEN_ID)
		{
			i_token = translate_redir(i_token, i_parser, lexer_blocks, parser_blocks);
			if (i_token == NULL)
				return (true);
		}
		i_token = i_token->next;
	}
	return (false);
}
