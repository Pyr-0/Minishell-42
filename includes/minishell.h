/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/20 21:57:17 by mrojas-e         ###   ########.fr       */
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
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "structs.h"
# include "env.h"
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "redir_creator.h"
# include "executor.h"

# define EXIT_PIPE_REDIR_ERROR	258
# define EXIT_STD_ERROR			1
# define PIPE_READ				0
# define PIPE_WRITE				1

int	g_exit_status;

void	fuck_sigpipe(int sig);

/*============PIPE_REDIR_ERRORS===============*/

bool	handle_error_and_free(t_lexer_block *lexer_block,
			t_parser_block *parser_blocks, char *error_message);
bool	redir_error(t_token *token);
bool	pipe_error(t_lexer_block *block);
bool	pipe_redir_error(t_lexer_block *lexer_block);

/*============TESTING STUFF===============*/

void	print_lexer_blocks(t_lexer_block *lexer_done);
void	print_parser_blocks(t_parser_block *parser_blocks);
void	print_exec_blocks(t_exec_block *exec_blocks);
void	print_env(void);

/*============BUILTINS===============*/

bool	cmd_echo(t_exec_block *echo);
bool	cmd_pwd(t_exec_block *cmd_pwd);
bool	cmd_cd(t_exec_block *cd);
bool	cmd_env(t_exec_block *cmd_env);
bool	cmd_export(t_exec_block *cmd_export);
bool	handle_error(char *msg, int exit_status);
char	*fetch_env_var_value(char *varname);

void test(t_parser_block *test);

#endif
