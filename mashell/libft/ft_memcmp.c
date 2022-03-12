/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 12:45:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/05 16:30:14 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	size_t			counter;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	counter = 0;
	while (counter < n)
	{
		if (string1[counter] != string2[counter])
			return (string1[counter] - string2[counter]);
		counter++;
	}
	return (0);
}
