/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 20:54:01 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/29 15:19:31 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		str[j++] = s1[i++];
	}
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		str[j++] = s2[i++];
	}
	str[j] = '\0';
	return (str);
}

/*frees both strings after the creation of the new one. this means that 
both of them need to be allocated beforehand!
they also still get freed when there happens a malloc error, need to be aware of that!*/
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (new == NULL)
		return (NULL);
	return (new);
}
