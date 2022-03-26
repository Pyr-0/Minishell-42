/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:04:58 by shaas             #+#    #+#             */
/*   Updated: 2022/03/16 20:17:58 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *old_mem, size_t size)
{
	char	*new_mem;

	if (old_mem == NULL || size == 0)
		return (NULL);
	new_mem = malloc(size);
	ft_memcpy(new_mem, old_mem, size);
	free(old_mem);
	return (new_mem);
}
