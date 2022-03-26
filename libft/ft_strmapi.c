/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 18:13:57 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/03 20:09:29 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	i = 0;
	if (s == 0 || f == 0)
		return (NULL);
	res = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[i] != 0)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
