/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 12:45:25 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/05 16:27:07 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	counter;
	size_t	len_of_small;
	char	*big_iter;

	len_of_small = ft_strlen(small);
	counter = 0;
	if (len_of_small == 0)
		return ((char *)big);
	while (big[counter] != '\0' && counter + (len_of_small - 1) < len)
	{
		big_iter = &((char *)big)[counter];
		if (ft_memcmp(big_iter, small, len_of_small) == 0)
			return (big_iter);
		counter++;
	}
	return (NULL);
}
