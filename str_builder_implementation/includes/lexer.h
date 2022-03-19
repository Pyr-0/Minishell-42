/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:44:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/19 14:30:03 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_str_builder{
	unsigned int	write_head; //index and length
	unsigned int	allocated_buffer_size;
	char			*buffer;
}	t_str_builder;

// typedef struct s_list{
// 	char			**cmd; 
// 	struct s_list	*next;
// }	t_list;

// typedef struct s_text{
// 	char			*content;
// 	struct s_list	*next;
// }	t_text;

// enum	e_operator{

// 		TOKEN_ID, 
// 		TOKEN_PIPE,
// 		TOKEN_STRING,
// 		TOKEN_BIGGER,
// 		TOKEN_SMALLER
// };

// typedef struct s_operator{
// 	char			*content; 
// 	enum e_operator	re_director;
// 	struct s_list	*next;
// }	t_operator;

void	str_builder_create(t_str_builder *build);
void	str_builder_destroy(t_str_builder *build);
void	str_builder_join_char(t_str_builder *build, char c);
void	str_builder_join_str(t_str_builder *build, char *s);
char	*str_builder_join_finalize(t_str_builder *build);


#endif