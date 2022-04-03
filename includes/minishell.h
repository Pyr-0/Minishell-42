/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/03 16:32:41 by mrojas-e         ###   ########.fr       */
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

# define EXIT_PIPE_REDIR_ERROR	258
# define EXIT_STD_ERROR			1

int	g_exit_status;

/*============PIPE_REDIR_ERRORS===============*/

bool	handle_error_and_free(t_lexer_block *lexer_block,
		t_parser_block *parser_blocks, char *error_message);
bool	redir_error(t_token *token);
bool	pipe_error(t_lexer_block *block);
bool	pipe_redir_error(t_lexer_block *lexer_block);

/*============TESTING STUFF===============*/

void	print_lexer_blocks(t_lexer_block *lexer_done);
void	print_parser_blocks(t_parser_block *parser_blocks);
void	print_env(void);

/*============BUILTINS===============*/
void	cmd_pwd(void);
void	cmd_echo(t_parser_block *echo);
void	cmd_cd(t_parser_block *cd);
void test(t_parser_block *test);

#endif
