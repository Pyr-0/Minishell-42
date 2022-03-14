/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/14 13:36:10 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int main()
{
	char *test;

	while(1)
	{

		test = readline("miSHELLin test be like : ");
		printf("Readline input :%s\n", test);
		printf("System command Exec:\n");
		system(test); //shows the output of commands
		t_lexer *lexer = init_lexer(test);

		t_token *token;
		token = (void *)0;
		while ((token = lexer_get_next_token(lexer)) != NULL)
			printf("TOKEN (%d, %s)\n", token->type, token->value);
	}
	return (0);
} 
