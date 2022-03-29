/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/29 14:40:27 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_INPUT_HEREDOC, // 2
		TOKEN_INPUT_FILE, // 3
		TOKEN_OUTPUT_REPLACE, // 4
		TOKEN_OUTPUT_APPEND // 5
	} e_type;
	char			*value; // will be NULL if is redirection
	struct s_token	*next;
}		t_token;

typedef struct s_lexer
{
	unsigned int	i;
	char			c;
	char			*contents;
	size_t			line_len;
}				t_lexer;

typedef struct s_command_block
{
	t_token					*tokens; // what if nothing in between pipes?
	struct s_command_block	*next;
	char					*block_contents;
}							t_command_block;


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

typedef enum e_expand
{
	EXPAND_DOUBLE_QUOTE = '"',
	EXPAND_SINGLE_QUOTE = '\'',
	EXPAND_DOLLAR_SIGN = '$'
}				t_expand;

typedef struct s_env
{
	char					*varname;
	char					*varvalue;
	struct s_env			*next;
}							t_env;

#endif
