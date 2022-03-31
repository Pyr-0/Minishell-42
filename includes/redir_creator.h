/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_creator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:38:54 by shaas             #+#    #+#             */
/*   Updated: 2022/03/31 18:41:26 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_CREATOR_H
# define REDIR_CREATOR_H

/*============REDIR_CREATOR===============*/

t_exec_block	*redir_creator(t_parser_block *parser_blocks);
void			exec_free_args(t_arg *args);
void			free_close_exec_blocks(t_exec_block *exec_blocks);
void			redir_creator_fail_exit(t_parser_block *parser_blocks, t_exec_block *exec_blocks);

#endif
