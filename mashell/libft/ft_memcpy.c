/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:13:25 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/06 17:53:46 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	counter;

	if (dst == src || n == 0)
		return (dst);
	if (!dst && !src)
		return (NULL);
	counter = 0;
	while (counter < n)
	{
		((unsigned char *) dst)[counter] = ((unsigned char *) src)[counter];
		counter++;
	}
	return (dst);
}
