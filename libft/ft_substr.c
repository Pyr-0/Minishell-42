/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 13:29:19 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/28 18:38:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start + len >= slen)
	{
		if (start > slen)
			len = 0;
		else
			len = slen - start;
	}
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	else
	{
		ft_strlcpy(str, s + start, len + 1);
		return (str);
	}
}

/* 
int	main(void)
{
	const char str[] = "Hello World";
	printf("%s", ft_substr(str, 6, 5));
}
 */
