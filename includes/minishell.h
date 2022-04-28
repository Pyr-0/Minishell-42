/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/28 18:56:06 by satori           ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <locale.h>

# include "../libft/libft.h"
# include "structs.h"
# include "env.h"
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "redir_creator.h"
# include "executor.h"

# define EXIT_STD_ERROR			1
# define EXIT_CMD_NOT_FOUND		127
# define EXIT_INVALID_EXIT		255
# define EXIT_PIPE_REDIR_ERROR	258
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
void	print_split(char **split);

/*============BUILTINS===============*/

bool	cmd_echo(t_exec_block *echo);
bool	cmd_pwd(t_exec_block *cmd_pwd);
bool	cmd_cd(t_exec_block *cd);
bool	cmd_env(t_exec_block *cmd_env);
bool	cmd_export(t_exec_block *cmd_export);
bool	handle_error(char *msg, int exit_status);
char	*fetch_env_var_value(char *varname);
void	unset_variable(t_arg *varname);
bool	cmd_unset(t_exec_block *cmd_unset);
int		cmd_exit(t_exec_block *cmd_exit, t_exec_block *exec_blocks);

/*============SIGNALS===============*/

void	sig_setter(void);
void	set_signal_heredoc(void);

#endif
