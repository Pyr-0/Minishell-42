/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/18 15:51:49 by shaas            ###   ########.fr       */
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
# include "../libft/libft.h"


// typedef struct s_list{
// 	char			**cmd; 
// 	struct s_list	*next;
// }	t_list;

// typedef struct s_text{
// 	char			*content;
// 	struct s_list	*next;
// }	t_text;

// enum	e_operator{

// 		TOKEN_ID, 
// 		TOKEN_PIPE,
// 		TOKEN_STRING,
// 		TOKEN_BIGGER,
// 		TOKEN_SMALLER
// };

// typedef struct s_operator{
// 	char			*content; 
// 	enum e_operator	re_director;
// 	struct s_list	*next;
// }	t_operator;

/* 
my idea: lexer goes through all the characters, when token found (that is not pipe/redirection), go into token collect mode. 
in that function, handle double and single quotes. own function for that. also function if closing quote exists in further string.
MALLOC CHECKS!
*/

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_INPUT_HEREDOC,
		TOKEN_INPUT_FILE,
		TOKEN_OUTPUT_REPLACE,
		TOKEN_OUTPUT_APPEND
	}	type;

	char *value; // will be NULL if is redirection
}	t_token;

typedef struct s_command_block
{
	t_token					*tokens; // what if nothing in between pipes?
	struct s_command_block	*next;
}	t_command_block;

typedef struct s_lexer
{
	char			c; //current character we are on
	unsigned int	i;
	char			*contents;
	size_t			linelen;
}	t_lexer;

void	init_lexer(t_lexer *lexer, char *contents);

void	lexer_advance(t_lexer *lexer);//moves the pointer to the next chaacter in the content

void	lexer_skip_whitespace(t_lexer *lexer);

t_command_block	*lexer(t_lexer *lexer);//get to next token (most logic is here)

t_token	*lexer_collect_string(t_lexer *lexer);//define how to parse the string
t_token *lexer_collect_id(t_lexer *lexer);

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

char *lexer_get_current_char_as_string(t_lexer *lexer);


/*============TOKENS===============*/

void	assign_token(t_token *token, int type, char *value);
t_token	*init_token(int type, char *value);

#endif