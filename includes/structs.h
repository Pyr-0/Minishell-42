/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/27 17:58:44 by mrojas-e         ###   ########.fr       */
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
	char					*value; // will be NULL if is redirection
	struct s_token			*next;
}		t_token;
typedef struct s_lexer
{
	unsigned int			i;
	char					c;
	char					*contents;
	size_t					line_len;
}							t_lexer;
typedef struct s_command_block
{
	t_token					*tokens; // what if nothing in between pipes?
	char					*block_contents;
	struct s_command_block	*next;
}							t_command_block;
enum
{
	EXPAND_DOUBLE_QUOTE = '"',
	EXPAND_SINGLE_QUOTE = '\'',
	EXPAND_DOLLAR_SIGN = '$'
}							e_expand;
typedef struct s_env
{
	char					*varname;
	char					*varvalue;
	struct s_env			*next;
}							t_env;
#endif