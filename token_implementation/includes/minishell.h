/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/22 19:53:24 by shaas            ###   ########.fr       */
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
my idea: lexer goes through all the characters, when token found (that is not pipe/redirection), go into token collect mode. 
in that function, handle double and single quotes. own function for that. also function if closing quote exists in further string.
MALLOC CHECKS!
*/

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_INPUT_HEREDOC,	// 1
		TOKEN_INPUT_FILE,		// 2
		TOKEN_OUTPUT_REPLACE,	// 3
		TOKEN_OUTPUT_APPEND		// 4
	}	type;

	char	*value; // will be NULL if is redirection
	struct s_token	*next;
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

void	init_lexer(t_lexer *lexer, char *contents);
t_token	*lexer_collect_string(t_lexer *lexer);
void	lexer_advance_with_token(t_lexer *lexer, int token_len);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
char	*ft_strjoin_free(char *s1, char *s2);
bool	is_seperator(char c);
void	lexer_collect_id(t_lexer *lexer, t_command_block *first, t_command_block *curr);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_command_block	*init_command_block(t_command_block *first);
t_command_block	*add_command_block(t_command_block *prev, t_command_block *first);
void	free_lexer(t_command_block *command_blocks);
void	lexer_fail_exit(t_command_block *command_blocks);
bool	lexer_peek_string(t_lexer *lexer, char *str);
void	check_for_tokens(t_lexer *lexer, t_command_block *iter, t_command_block *first);
t_command_block	*lexer(t_lexer *lexer);


/*============TOKENS===============*/

t_token	*init_token(int type, char *value, t_command_block *first);
int	add_token(int type, char *value, t_command_block *curr, t_command_block *first);

#endif