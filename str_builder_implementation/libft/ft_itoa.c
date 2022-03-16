/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 12:39:00 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/08/05 16:29:54 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_intlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}	
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		ndigits;
	long	temp;

	temp = n;
	ndigits = ft_intlen(temp);
	ptr = ft_calloc(sizeof(char), ndigits + 1);
	if (!ptr)
		return (NULL);
	if (temp < 0)
		temp = temp * (-1);
	while (ndigits > 0)
	{
		ptr[ndigits - 1] = temp % 10 + '0';
		ndigits--;
		temp = temp / 10;
	}
	if (n < 0)
		ptr[ndigits] = '-';
	return (ptr);
}
