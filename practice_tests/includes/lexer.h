/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/12 18:12:11 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// #include "token.h"
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>


typedef struct s_lexer
{
	char			c; //current character we are on
	unsigned int	i;
	char			*contents;
}	t_lexer;

typedef struct s_token
{
	enum
	{
		TOKEN_ID, //metacharachter
		TOKEN_EQUALS,
		TOKEN_SEMI,
		TOKEN_STRING,
		TOKEN_BIGGER,
		TOKEN_PAR_LEFT,
		TOKEN_PAR_RIGHT,
		TOKEN_SMALLER
	}	type;

	char *value;
}	t_token;

t_lexer	*init_lexer(char *contents);

void	lexer_advance(t_lexer *lexer);//moves the pointer to the next chaacter in the content

void	lexer_skip_whitespace(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer *lexer);//get to next token (most logic is here)

t_token	*lexer_collect_string(t_lexer *lexer);//define how to parse the string
t_token *lexer_collect_id(t_lexer *lexer);

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

char *lexer_get_current_char_as_string(t_lexer *lexer);


/*============TOKENS===============*/

void	assign_token(t_token *token, int type, char *value);
t_token	*init_token(int type, char *value);

#endif