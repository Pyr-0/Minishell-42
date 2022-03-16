/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/16 20:55:05 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int main()
{
	char	*test;
	t_lexer	lexer;

	while(1)
	{

		test = readline("miSHELLin$ ");
		printf("Readline input :%s\n", test);
		printf("System command exec:\n");
		system(test); //shows the output of commands
		init_lexer(&lexer, test);

		t_token *token;
		token = (void *)0;
		while ((token = lexer_get_next_token(&lexer)) != NULL)
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
