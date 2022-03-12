/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:35:14 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/12 19:33:10 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int main(int argc, char **argv)
{
	argc = 0;
	argv = NULL;

	t_lexer *lexer = init_lexer("var name = > \"john doe\" ; \n"
								"print(name) ; \n");

	t_token *token;

	token = (void *)0;

	while ((token = lexer_get_next_token(lexer)) != (void *)0)
		printf("TOKEN (%d, %s)\n", token->type, token->value);
	return (0);
} 