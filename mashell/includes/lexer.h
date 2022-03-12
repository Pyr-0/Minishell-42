/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/11 19:42:43 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_str_builder{
	unsigned int	write_head; //index and length
	unsigned int	allocated_buffer_size;
	char			*buffer;
}	t_str_builder;


void	str_builder_create(t_str_builder *build);
void	str_builder_destroy(t_str_builder *build);
void	str_builder_join_char(t_str_builder *build, char c);
void	str_builder_join_str(t_str_builder *build, char *s);
char	*str_builder_join_finalize(t_str_builder *build);


#endif