/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 21:43:02 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/01 20:09:28 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = ft_strlen(s1);
	result = ft_calloc(i + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		result[j] = s1[j];
		j++;
	}
	return (result);
}
