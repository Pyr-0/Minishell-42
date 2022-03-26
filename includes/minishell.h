/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/26 14:39:49 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "lexer.h"

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

enum
{
	EXPAND_DOUBLE_QUOTE = '"',
	EXPAND_SINGLE_QUOTE = '\'',
	EXPAND_DOLLAR_SIGN = '$'
}	expand;

typedef struct s_env
{
	char			*varname;
	char			*varvalue;
	struct s_env	*next;
}	t_env;

/*============INIT_ENV=============*/

char	*env_get_current_char_as_string(char c);
char	*get_varname(char *env_str);
char	*get_varvalue(char *env_str);
t_env	*init_env_node(char *env_str, t_env *first);
t_env	*add_env_node(char *env_str, t_env *prev, t_env *first);
t_env	*init_env(char *envp[]);
void	free_env(t_env *env);
void	env_fail_exit(t_env *env);

/*============EXPANDER===============*/

char	*expander_get_current_char_as_string(char c);
char	*collect_varname(char **iter, bool is_in_double_quotes);
char	*collect_varvalue(t_env *env, char *varname);
void	replace_dollar_sign(char *varvalue, char **iter, t_token *token);
char	*expand_dollar_sign(char **iter, t_token *token, t_env *env, bool is_in_double_quotes);
void	expand_token(t_token *token, t_env *env);
void	expander(t_command_block *lexer, t_env *env);
void	parser_expander(t_command_block *lexer, t_env *env);

/*============PIPE_REDIR_ERRORS===============*/

bool	handle_error_and_free(t_command_block *lexer_block, char *error_message);
bool	redir_error(t_token *token);
bool	pipe_error(t_command_block *block);
bool	pipe_redir_error(t_command_block *lexer_block);

#endif
