/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/25 17:37:42 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include "../libft/libft.h"

/* 
lexer.h again?
*/

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_PIPE,				// 1
		TOKEN_INPUT_HEREDOC,	// 2
		TOKEN_INPUT_FILE,		// 3
		TOKEN_OUTPUT_REPLACE,	// 4
		TOKEN_OUTPUT_APPEND		// 5
	}	type;

	char	*value; // will be NULL if is redirection
	struct s_token	*next;
}	t_token;

typedef struct s_command_block
{
	t_token					*tokens; // what if nothing in between pipes?
	char					*block_contents;
	struct s_command_block	*next;
}	t_command_block;

//{
//	enum	type;
//	char	*id;
//}
//
//typedef struct s_command_block
//{
//	char	*cmd;
//	t_arg	*arg;
//	t_redir	*input;
//	t_redir	*output; // what if nothing in between pipes?
//	struct s_command_block	*next;
//}	t_command_block;

typedef struct s_lexer
{
	unsigned int	i;
	char			c;
	char			*contents;
	size_t			line_len;
}	t_lexer;


/*============LEXER=============*/

void			init_lexer(t_lexer *lexer);
char			*lexer_collect_string(t_lexer *lexer);
void			lexer_advance_with_token(t_lexer *lexer, int token_len);
char			*lexer_get_current_char_as_string(t_lexer *lexer);
char			*ft_strjoin_free(char *s1, char *s2);
bool			is_seperator(char c);
bool			lexer_quote_is_closed(t_lexer *lexer);
void			lexer_collect_id(t_lexer *lexer, t_command_block *first, t_command_block *curr);
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
t_command_block	*init_command_block(t_command_block *first, char *block_contents);
t_command_block	*add_command_block(t_command_block *prev, t_command_block *first);
void			free_lexer(t_command_block *command_blocks);
void			lexer_fail_exit(t_command_block *command_blocks);
bool			lexer_peek_string(t_lexer *lexer, char *str);
void			check_for_tokens(t_lexer *lexer, t_command_block **iter, t_command_block *first);
t_command_block	*lexer(t_lexer *lexer);


/*============TOKENS===============*/

t_token	*init_token(int type, char *value, t_command_block *first);
int	add_token(int type, char *value, t_command_block *curr, t_command_block *first);

#endif