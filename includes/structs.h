/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/01 23:24:56 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* >============LEXER===============< */

typedef struct s_lexer{
	unsigned int	i;
	char			c;
	char			*contents;
	size_t			line_len;
}				t_lexer;

typedef struct s_token{
	enum
	{
		TOKEN_ID,
		TOKEN_INPUT_HEREDOC,
		TOKEN_INPUT_FILE,
		TOKEN_OUTPUT_REPLACE,
		TOKEN_OUTPUT_APPEND
	} e_type;
	char			*value;
	struct s_token	*next;
}		t_token;

// *block_contents - this is the return of readline,
// so the whole line. needed in case of an error to free it.

typedef struct s_lexer_block{
	t_token					*tokens;
	struct s_lexer_block	*next;
	char					*block_contents;
}							t_lexer_block;

/* >============PARSER===============< */

typedef struct s_arg{
	char					*value;
	struct s_arg			*next;
}	t_arg;

typedef struct s_redir{
	enum
	{
		REDIR_INPUT_HEREDOC,
		REDIR_INPUT_FILE,
		REDIR_OUTPUT_REPLACE,
		REDIR_OUTPUT_APPEND
	} e_redir_type;
	char					*id;
	struct s_redir			*next;
}					t_redir;

typedef struct s_parser_block{
	char					*cmd;
	t_arg					*arg;
	t_redir					*redir;
	struct s_parser_block	*next;
}	t_parser_block;

/* >============EXPANDER===============< */

typedef enum e_expand{
	EXPAND_DOUBLE_QUOTE =	'"',
	EXPAND_SINGLE_QUOTE =	'\'',
	EXPAND_DOLLAR_SIGN =	'$'
}				t_expand;

/* >============EXECUTOR===============< */

typedef struct s_exec_block{
	char					*cmd;
	t_arg					*arg;
	int						in_fd;
	int						out_fd;
	struct s_exec_block		*next;
}	t_exec_block;

/* >============ENVIRONMENT===============< */

typedef struct s_env{
	char					*varname;
	char					*varvalue;
	struct s_env			*next;
}							t_env;

#endif
