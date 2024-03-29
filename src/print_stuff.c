/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:36:41 by shaas             #+#    #+#             */
/*   Updated: 2023/12/05 17:25:08 by shaas            ###   ########.fr       */
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
			printf("token_type: %d, token_value: %s\n",
				i_token->e_type, i_token->value);
			i_token = i_token->next;
		}
		printf("\n");
		i_block = i_block->next;
	}
	printf("\e[44mprint lexer blocks end\e[0m\n\n");
}

void	print_redirs(t_parser_block *i_block)
{
	t_redir	*i_redir;

	i_redir = i_block->redir;
	printf("redirections:\n");
	while (i_redir != NULL)
	{
		printf("	redir_type: %u, redir_id: %s\n",
			i_redir->e_redir_type, i_redir->id);
		i_redir = i_redir->next;
	}
}

void	print_parser_blocks(t_parser_block *parser_blocks)
{
	t_parser_block	*i_block;
	t_arg			*i_arg;

	i_block = parser_blocks;
	printf("\n\e[102mprint parser blocks start\e[0m\n");
	while (i_block != NULL)
	{
		printf("\e[92mnew parser block:\e[0m\n");
		printf("command: %s\n", i_block->cmd);
		i_arg = i_block->arg;
		printf("arguments:\n");
		while (i_arg != NULL)
		{
			printf("	arg_value: %s\n", i_arg->value);
			i_arg = i_arg->next;
		}
		print_redirs(i_block);
		printf("\n");
		i_block = i_block->next;
	}
	printf("\e[102mprint parser blocks end\e[0m\n\n");
}

void	print_exec_blocks(t_exec_block *exec_blocks)
{
	t_exec_block	*i_block;
	t_arg			*i_arg;

	i_block = exec_blocks;
	printf("\n\033[48:5:172mprint exec blocks start\e[0m\n");
	while (i_block != NULL)
	{
		printf("\033[38;5;172mnew exec block:\e[0m\n");
		printf("command: %s\n", i_block->cmd);
		i_arg = i_block->arg;
		printf("arguments:\n");
		while (i_arg != NULL)
		{
			printf("	arg_value: %s\n", i_arg->value);
			i_arg = i_arg->next;
		}
		printf("input_fd: %d\n", i_block->in_fd);
		printf("output_fd: %d\n", i_block->out_fd);
		printf("\n");
		i_block = i_block->next;
	}
	printf("\033[48:5:172mprint exec blocks end\e[0m\n\n");
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
