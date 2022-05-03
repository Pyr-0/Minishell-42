/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 12:44:33 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/03 19:31:42 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\t')
		return (1);
	return (0);
}

bool	ft_atoi(const char *str, int *res)
{
	int		sign;
	long	result;
	int		counter;

	sign = 1;
	result = 0;
	counter = 0;
	while (ft_isspace(str[counter]))
		counter ++;
	if (str[counter] == '+')
		counter++;
	else if (str[counter] == '-')
	{
		sign = -1;
		counter++;
	}
	while (ft_isdigit(str[counter]))
	{
		result = result * 10 + (str[counter] - '0');
		counter++;
	}
	*res = result * sign;
	return (true);
}
