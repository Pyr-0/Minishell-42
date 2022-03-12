/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:24:56 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/12 19:45:19 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

//#include "includes/token.h"

t_token *init_token(int type, char *value)
{
	t_token	*token = calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	
	return (token);
}
/*alternative so the allocation gets done separately to avoid
	leaks and constant freeing.*/
/* void	assign_token(t_token *token, int type, char *value)
{
	token->type = type;
	token->value = value;	
	return (token);
}

t_token *init_token(int type, char *value)
{
	t_token	*token = calloc(1, sizeof(t_token));
	if (token != NULL)
	{
		assign_token(token, type, value);
	}	
	return (token);
}
 */