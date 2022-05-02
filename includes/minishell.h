/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 20:45:55 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"

# define EXIT_STD_ERROR			1
# define EXIT_CMD_NOT_FOUND		127
# define EXIT_INVALID_EXIT		255
# define EXIT_PIPE_REDIR_ERROR	258
# define READ				0
# define WRITE				1

int	g_exit_status;

/* >============PIPE_REDIR_ERRORS===============< */

bool	handle_error_and_free(t_lexer_block *lexer_block,
			t_parser_block *parser_blocks, char *error_message);
bool	redir_error(t_token *token);
bool	pipe_error(t_lexer_block *block);
bool	pipe_redir_error(t_lexer_block *lexer_block);

/* >============TESTING STUFF===============< */

void	print_lexer_blocks(t_lexer_block *lexer_done);
void	print_parser_blocks(t_parser_block *parser_blocks);
void	print_exec_blocks(t_exec_block *exec_blocks);
void	print_env(void);
void	print_split(char **split);

/* >============SIGNALS===============< */

void	set_signals(void);
void	set_signal_heredoc(void);
void	fuck_sigpipe(int sig);
void	clear_signals(void);
void	signalhandler_ctrlc(int sig);
void	signal_handler_heredoc(int sig);
void	signalhandler_ctrl_child(int sig);
void	exit_signal(void);
void	progress_bar(void);

#endif
