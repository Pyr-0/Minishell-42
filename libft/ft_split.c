/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:16:46 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/25 22:56:17 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_count(const char *s1, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] == c)
			i++;
		if (s1[i] != '\0')
			wcount += 1;
		while (s1[i] != c && s1[i] != '\0')
			i++;
	}
	return (wcount);
}

char	*ft_helper(const char *s1, int *start, char c)
{
	int	temp;
	int	end;

	while (s1[*start] == c)
		(*start)++;
	end = *start;
	while (s1[end] != c && s1[end] != '\0')
		end++;
	temp = *start;
	*start = end;
	return (ft_substr(s1, temp, end - temp));
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free (split);
}

char	**ft_split(const char *s1, char c)
{
	int		start;
	int		words;
	int		wcount;
	char	**res;

	if (!s1)
		return (NULL);
	start = 0;
	words = 0;
	wcount = ft_count(s1, c);
	res = ft_calloc(wcount + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (words < wcount && s1[start] != '\0')
	{
		res[words] = ft_helper(s1, &start, c);
		if (res[words++] == 0)
			return (NULL);
	}
	return (res);
}
