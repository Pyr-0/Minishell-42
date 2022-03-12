/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:16:05 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/12 14:34:25 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#include "../includes/lexer.h"

void	str_builder_create(t_str_builder *build)
{
	build->write_head = 0;
	build->allocated_buffer_size = 0;
	(*build).buffer = NULL;
}
void	str_builder_destroy(t_str_builder *build)
{
	if(build->buffer != NULL)
		free(build->buffer);
}
void	str_builder_join_char(t_str_builder *build, char c)
{
	//reallocate if you overflow the bff size ( insert char right point )
	if (build->write_head < build->allocated_buffer_size)
		{
			build->buffer[build->write_head] = c;
			build->write_head++;
		}
}
void	str_builder_join_str(t_str_builder *build, char *s)
{
	while (*s != '\0')
	{
		str_builder_join_char(build, *s);
		s++;
	}
	return ;
}

char	*str_builder_join_finalize(t_str_builder *build)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(build->write_head + 1);
	if (temp != NULL)
	{
		while (i < build->write_head)
		{
			temp[i] = build->buffer[i];
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
