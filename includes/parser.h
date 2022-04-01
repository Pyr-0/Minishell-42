/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:08:46 by shaas             #+#    #+#             */
/*   Updated: 2022/04/01 19:38:09 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*============PARSER===============*/

t_parser_block	*parser(t_lexer_block *lexer_block);
void			free_parser_blocks(t_parser_block *parser_blocks);
void			parser_fail_exit(t_lexer_block *lexer_blocks, t_parser_block *parser_blocks);
void			parser_free_redir(t_redir *redir);
void			parser_free_args(t_arg *args);
int				get_lexer_block_num(t_lexer_block *lexer_blocks);
t_parser_block	*create_parser_blocks(t_lexer_block *lexer_blocks);
void	add_cmd(t_parser_block *i_parser, t_token *i_token,
			t_parser_block *parser_blocks, t_lexer_block *lexer_blocks);
void	add_redir_id(t_parser_block *i_parser, t_token *i_token,
			t_parser_block *parser_blocks, t_lexer_block *lexer_blocks);
t_parser_block	*init_parser_block(t_lexer_block *lexer_blocks, t_parser_block *first);
t_redir			*init_redir(t_lexer_block *lexer_blocks, t_parser_block *first);
t_arg			*init_arg(t_lexer_block *lexer_blocks, t_parser_block *first);
void			add_arg(t_parser_block *first, char *value,
			t_lexer_block *lexer_blocks, t_parser_block *curr);
t_parser_block	*add_parser_block(t_parser_block *first, t_parser_block *prev,
			t_lexer_block	*lexer_blocks);
void			add_redir(t_parser_block *first, int redir_type,
			t_lexer_block *lexer_blocks, t_parser_block *curr);
bool	translate_lexer_to_parser_block(t_lexer_block *i_lexer,t_parser_block *i_parser,
								t_lexer_block *lexer_blocks, t_parser_block *parser_blocks);

#endif
