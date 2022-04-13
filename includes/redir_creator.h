/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:38:54 by shaas             #+#    #+#             */
/*   Updated: 2022/04/13 19:17:48 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_CREATOR_H
# define REDIR_CREATOR_H

/*============REDIR_CREATOR===============*/

t_exec_block	*redir_creator(t_parser_block *parser_blocks);
t_exec_block	*create_exec_blocks(t_parser_block *parser_blocks);
void			exec_free_args(t_arg *args);
void			free_close_exec_blocks(t_exec_block *exec_blocks);
void			redir_creator_fail_exit1(t_parser_block *parser_blocks,
					t_exec_block *exec_blocks);
void			redir_creator_fail_exit2(t_parser_block *parser_blocks,
		t_exec_block *exec_blocks);
int				get_parser_block_num(t_parser_block *parser_blocks);
void			copy_cmd_and_args_to_exec(t_exec_block *first_exec,
	t_parser_block *first_parser);
void			free_parser_blocks_only_redir(t_parser_block *parser_blocks);

#endif
