/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 18:11:15 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/07/09 18:20:45 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_s;
	size_t			counter;

	char_s = (unsigned char *)s;
	counter = 0;
	while (counter < n)
	{
		if (char_s[counter] == (unsigned char)c)
			return (&char_s[counter]);
		counter++;
	}
	return (NULL);
}
