/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/22 21:59:44 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	char			*test;
	t_lexer			lexer_struct;
	t_command_block	*lexer_passed = NULL;

	t_command_block	*i_block;
	t_token			*i_token;

	while(1)
	{
		test = readline("mi[SHELL]in$ ");
		printf("Readline input is:%s\n", test);
		printf("System command exec:\n");
		system(test);
		init_lexer(&lexer_struct, test);

		lexer_passed = lexer(&lexer_struct);
		i_block = lexer_passed;
		while (i_block != NULL)
		{
			printf("new command block:\n");
			i_token = i_block->tokens;
			while (i_token != NULL)
			{
				printf("token_type: %d, token_value: %s\n", i_token->type, i_token->value);
				i_token = i_token->next;
			}
			i_block = i_block->next;
		}
		free_lexer(lexer_passed);
		printf("\n");
		//system("leaks minishell");
		break ; // testing
	}
	return (0);
}