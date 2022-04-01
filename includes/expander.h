/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:07:18 by shaas             #+#    #+#             */
/*   Updated: 2022/04/01 21:55:44 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_EXPANDER_H
# define PARSER_EXPANDER_H

/*============EXPANDER===============*/

void	expander(t_lexer_block *lexer);
void	expand_token(t_token *token, t_lexer_block *first);
void	expand_double_quotes(char **iter, char **new_token_value, t_lexer_block *first);
void	expand_single_quotes(char **iter, char **new_token_value, t_lexer_block *first);
void	expand_dollar_sign(char **iter, char **new_token_value, t_lexer_block *first);
char	*collect_varname(char **iter, t_lexer_block *first);
char	*collect_varvalue(char *varname);
void	expander_advance_with_char(char **iter, char **str, t_lexer_block *first);
char	*expander_get_current_char_as_string(char c, t_lexer_block *first);
void	expander_init_new_value(t_token *token, char *new_value);
bool	expander_quote_is_closed(char *iter);

#endif