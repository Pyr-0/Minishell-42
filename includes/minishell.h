/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/29 15:31:02 by shaas            ###   ########.fr       */
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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "lexer.h"
# include "env.h"
# include "../libft/libft.h"

# define EXIT_PIPE_REDIR_ERROR 258

int	g_exit_status;

/*============EXPANDER===============*/

char	*expander_get_current_char_as_string(char c, t_command_block *first);
char	*collect_varname(char **iter, t_command_block *first);
char	*collect_varvalue(char *varname, t_command_block *first);
void	expand_dollar_sign(char **iter, char **new_token_value, t_command_block *first);
void	expand_token(t_token *token, t_command_block *first);
void	expander(t_command_block *lexer);
void	parser_expander(t_command_block *lexer);

/*============PIPE_REDIR_ERRORS===============*/

bool	handle_error_and_free(t_command_block *lexer_block,
			char *error_message);
bool	redir_error(t_token *token);
bool	pipe_error(t_command_block *block);
bool	pipe_redir_error(t_command_block *lexer_block);

/*============TESTING STUFF===============*/

void	print_tokens(t_command_block *lexer_done);
void	print_env(void);

#endif
