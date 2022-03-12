/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:56:38 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/01 20:15:08 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;
	size_t	count;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	count = dlen;
	if (dlen >= dstsize)
		return (slen + dstsize);
	while (count < dstsize - 1 && src[i] != '\0')
	{
		dst[count] = src[i];
		i++;
		count++;
	}
	dst[count] = '\0';
	return (dlen + slen);
}
