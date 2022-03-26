/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 12:44:43 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/04 19:26:26 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*ptr;
	size_t	size_in_bytes;

	size_in_bytes = nitems * size;
	ptr = (char *)malloc(size_in_bytes);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size_in_bytes);
	return (ptr);
}
