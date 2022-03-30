/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:36:41 by shaas             #+#    #+#             */
/*   Updated: 2022/03/30 22:04:11 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_lexer_blocks(t_lexer_block *lexer)
{
	t_lexer_block	*i_block;
	t_token			*i_token;

	i_block = lexer;
	printf("\n\e[44mprint lexer blocks start\e[0m\n");
	while (i_block != NULL)
	{
		printf("\e[34mnew lexer block:\e[0m\n");
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			printf("token_type: %d, token_value: %s\n", i_token->e_type, i_token->value);
			i_token = i_token->next;
		}
		printf("\n");
		i_block = i_block->next;
	}
	printf("\e[44mprint lexer blocks end\e[0m\n\n");
}

void	print_parser_blocks(t_parser_block *parser_blocks)
{
	t_arg	*i_arg;
	t_redir	*i_redir;

	printf("\n\e[102mprint parser blocks start\e[0m\n");
	while (parser_blocks != NULL)
	{
		printf("\e[92mnew parser block:\e[0m\n");
		printf("command: %s\n", parser_blocks->cmd);
		i_arg = parser_blocks->arg;
		printf("arguments:\n");
		while (i_arg != NULL)
		{
			printf("	arg_value: %s\n", i_arg->value);
			i_arg = i_arg->next;
		}
		i_redir = parser_blocks->input;
		printf("inputs:\n");
		while (i_redir != NULL)
		{
			printf("	input_type: %u, input_id: %s\n", i_redir->e_redir_type, i_redir->id);
			i_redir = i_redir->next;
		}
		i_redir = parser_blocks->output;
		printf("outputs:\n");
		while (i_redir != NULL)
		{
			printf("	output_type: %u, output_id: %s\n", i_redir->e_redir_type, i_redir->id);
			i_redir = i_redir->next;
		}
		printf("\n");
		parser_blocks= parser_blocks->next;
	}
	printf("\e[102mprint parser blocks end\e[0m\n\n");
}

void	print_env(void)
{
	t_env	*env;
	env = *(get_env(NULL));
	printf("\n\e[45mprint env start\e[0m\n");
	while (env != NULL)
	{
		printf("%s=%s\n", env->varname, env->varvalue);
		env = env->next;
	}
	printf("\e[45mprint env end\e[0m\n\n");
}
