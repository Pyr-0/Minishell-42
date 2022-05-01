/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:08:55 by mrojas-e          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/01 22:25:55 by mrojas-e         ###   ########.fr       */
=======
/*   Updated: 2022/05/01 19:29:04 by shaas            ###   ########.fr       */
>>>>>>> 39b244d52a78a9e850904f9475e4db15e516d6d5
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	progress_bar(void)
{
	int			i;
	char		bar[102];
	const char	*lable;

	i = 0;
	lable = "|/-\\";
	ft_memset(bar, 0, 102 * sizeof(char));
	printf("\e[36m\
                                    LOADING PLEASE WAIT ...\e[0m\n");
	while (i <= 100)
	{
		bar[i] = '#';
		printf("\r\e[4;35m\e[40m\e[1;98m[%-2s]\e[0m\e[36m [%d%%] [%c]", bar,
			i, lable[i % 4]);
		usleep(3000);
		fflush(stdout);
		i++;
	}
	printf("\n");
}
	//printf("\r\e[36m [%d%%] [%c]\n",i,lable[i%4]); line by line %
