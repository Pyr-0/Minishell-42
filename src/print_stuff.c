/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:36:41 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 18:49:53 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_lexer_block *lexer)
{
	t_lexer_block	*i_block;
	t_token			*i_token;

	i_block = lexer;
	printf("\e[44mprint token start\e[0m\n");
	while (i_block != NULL)
	{
		printf("\e[34mnew command block:\e[0m\n");
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			printf("token_type: %d, token_value: %s\n", i_token->e_type, i_token->value);
			i_token = i_token->next;
		}
		printf("\n");
		i_block = i_block->next;
	}
	printf("\e[44mprint token end\e[0m\n\n");
}

void	print_env(void)
{
	t_env	*env;
	env = *(get_env(NULL));
	printf("\e[45mprint env start\e[0m\n");
	while (env != NULL)
	{
		printf("%s=%s\n", env->varname, env->varvalue);
		env = env->next;
	}
	printf("\e[45mprint env end\e[0m\n\n");
}
