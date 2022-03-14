/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/14 17:55:14 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// #include "token.h"
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <readline/readline.h>


typedef struct s_list{
	char			**cmd; //current character we are on
	struct s_list	*next;
}	t_list;

typedef struct s_text{
	char			*content; //current character we are on
	struct s_list	*next;
}	t_text;

enum	e_operator{

		TOKEN_ID, //metacharachter
		TOKEN_PIPE,
		TOKEN_STRING,
		TOKEN_BIGGER,
		TOKEN_SMALLER
};

typedef struct s_operator{
	char			*content; //current character we are on
	enum e_operator	re_director;
	struct s_list	*next;

}	t_operator;


typedef struct s_token{
	enum
	{
		TOKEN_ID, //metacharachter
		TOKEN_PIPE,
		TOKEN_STRING,
		TOKEN_BIGGER,
		TOKEN_SMALLER
	}	type;

	char *value;
}	t_token;
typedef struct s_lexer
{
	char			c; //current character we are on
	unsigned int	i;
	char			*contents;
}	t_lexer;


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