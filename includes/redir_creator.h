/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:38:54 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 22:32:50 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_CREATOR_H
# define REDIR_CREATOR_H

/* >============REDIR CREATOR===============< */

t_exec_block	*redir_creator(t_parser_block *parser_blocks);
void			create_pipe(t_exec_block *i_exec, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks);
bool			handle_redirs_of_one_block(t_exec_block *i_exec,
					t_parser_block *i_parser, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks);

/* >============REDIR CREATOR INITS===============< */
t_exec_block	*create_exec_blocks(t_parser_block *parser_blocks);
t_exec_block	*init_exec_block(t_parser_block *parser_blocks,
					t_exec_block *first);
t_exec_block	*add_exec_block(t_exec_block *first, t_exec_block *prev,
					t_parser_block *parser_blocks);
void			copy_cmd_and_args_to_exec(t_exec_block *first_exec,
					t_parser_block *first_parser);

/* >============REDIR CREATOR UTILS===============< */
int				get_parser_block_num(t_parser_block *parser_blocks);
void			replace_fd(int *old_fd, int new_fd);
bool			redir_creator_handle_error(char *file, char *msg);
bool			redir_handler_fail(t_exec_block *i_exec);

/* >============REDIR CREATOR FREE/EXIT===============< */
void			redir_creator_fail_exit1(t_parser_block *parser_blocks,
					t_exec_block *exec_blocks);
void			redir_creator_fail_exit2(t_parser_block *parser_blocks,
					t_exec_block *exec_blocks);
void			free_close_exec_blocks(t_exec_block *exec_blocks);
void			exec_free_args(t_arg *args);
void			free_parser_blocks_only_redir(t_parser_block *parser_blocks);

/* >============REDIR CREATOR HANDLE FILES===============< */
bool			handle_redir_files(t_exec_block *i_exec,
					t_parser_block *i_parser);
bool			open_input_file(t_redir *input, t_exec_block *curr);
bool			open_output_file(t_redir *output, t_exec_block *curr);

/* >============REDIR CREATOR HANDLE HEREDOCS===============< */
int				handle_heredocs(t_parser_block *i_parser,
					t_exec_block *exec_blocks, t_parser_block *parser_blocks);
bool			read_heredoc(int *heredoc_pp,
					t_redir *i_redir, t_exec_block *exec_blocks,
					t_parser_block *parser_blocks);
int				init_i_exec_with_heredoc(int *heredoc_pp,
					t_parser_block *i_parser);
bool			check_if_last_input_is_heredoc(t_parser_block *i_parser);
void			read_heredoc_fail_exit(int *heredoc_pp);

#endif
