/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/19 14:45:29 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	char	*test;
	t_lexer	lexer;

	while(1)
	{

		test = readline("mi[SHELL]in$");
		printf("Readline input is:%s\n", test);
		printf("System command exec:\n");
		system(test);
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
