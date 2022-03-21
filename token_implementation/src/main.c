/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/20 21:12:57 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	char			*test;
	t_command_block	*lexer_passed = NULL;

	while(1)
	{

		test = readline("mi[SHELL]in$");
		printf("Readline input is:%s\n", test);
		printf("System command exec:\n");
		system(test);
		init_lexer(lexer_passed, test);

		t_token *token;
		token = (void *)0;
		while ((token = lexer(lexer_passed)) != NULL)
		{
			printf("TOKEN (%d, %s)\n", token->type, token->value);
			free(token->value);
			free(token);
		}
		printf("\n");
		//system("leaks minishell");
	}
	return (0);
}