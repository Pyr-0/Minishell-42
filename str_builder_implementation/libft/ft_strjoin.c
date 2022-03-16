/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 20:54:01 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/09/07 23:44:24 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str != NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j++] = s2[i++];
	}
	str[j] = '\0';
	return (str);
}
