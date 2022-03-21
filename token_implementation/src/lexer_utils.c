/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:27:59 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/21 21:29:12 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


bool	is_seperator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0')
		return (true);
	return (false);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
	{
		lexer_advance(lexer);
	}
}

void	lexer_fail_exit(t_command_block *command_blocks)
{
	free_lexer(command_blocks);
	exit(EXIT_FAILURE);
}
