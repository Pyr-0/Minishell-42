/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 19:02:56 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/03 20:11:27 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (ft_strchr(set, s[i]) != 0)
			i++;
		else
			return (i);
	}
	return (i);
}

static int	ft_end(char const *s, char const *set)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (ft_strchr(set, s[i]) != 0)
			i--;
		else
			return (i);
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		start;
	int		end;

	if (s1 == 0 || set == 0)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start > end)
		strim = ft_strdup("");
	else
		strim = ft_substr(s1, start, end - start + 1);
	if (!strim)
		return (NULL);
	return (strim);
}
