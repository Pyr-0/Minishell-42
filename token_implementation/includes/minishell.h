/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/19 15:10:40 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <readline/readline.h>
# include "../libft/libft.h"

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
	unsigned int	i;
	char			c;
	char			*contents;
	size_t			line_len;
}	t_lexer;

/*============LEXER=============*/

void			init_lexer(t_lexer *lexer, char *contents);
void			lexer_advance(t_lexer *lexer);//moves the pointer to the next chaacter in the content
void			lexer_skip_whitespace(t_lexer *lexer);
t_command_block	*lexer(t_lexer *lexer);//get to next token (most logic is here)
t_token			*lexer_collect_string(t_lexer *lexer);//define how to parse the string
t_token			*lexer_collect_id(t_lexer *lexer);
t_token			*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char			*lexer_get_current_char_as_string(t_lexer *lexer);


/*============TOKENS===============*/

void			assign_token(t_token *token, int type, char *value);
t_token			*init_token(int type, char *value);

#endif