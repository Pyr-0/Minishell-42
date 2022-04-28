/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:37:18 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/28 18:56:12 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* >============LEXER===============< */

t_lexer_block	*lexer(t_lexer *lexer);
void			lexer_check_for_tokens(t_lexer *lexer,
					t_lexer_block **iter, t_lexer_block *first);

/* >============LEXER ADVANCE AND COLLECT===============< */
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
void			lexer_advance_with_token(t_lexer *lexer, int token_len);
void			lexer_collect_id(t_lexer *lexer, t_lexer_block *first,
					t_lexer_block *curr);
char			*lexer_collect_string(t_lexer *lexer, t_lexer_block *first);

/* >============LEXER INIT STRUCTS===============< */
void			init_lexer(t_lexer *lexer);
t_lexer_block	*add_lexer_block(t_lexer_block *prev,
					t_lexer_block *first);
t_lexer_block	*init_lexer_block(t_lexer_block *first,
					char *block_contents);
int				add_token(int type, char *value, t_lexer_block *curr,
					t_lexer_block *first);
t_token			*init_token(int type, char *value, t_lexer_block *first);

/* >============LEXER UTILS===============< */
char			*lexer_get_current_char_as_string(t_lexer *lexer,
					t_lexer_block *first);
bool			lexer_peek_string(t_lexer *lexer, char *str);
bool			lexer_quote_is_closed(t_lexer *lexer);
bool			is_seperator(char c);

/* >============LEXER FREE/EXIT===============< */
void			lexer_blocks_fail_exit(t_lexer_block *lexer_blocks);
void			free_lexer_blocks(t_lexer_block *lexer_blocks);

#endif