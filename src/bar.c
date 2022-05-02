/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:08:55 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 17:54:13 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	//printf("\r\e[36m [%d%%] [%c]\n",i,lable[i%4]); line by line %
void	progress_bar(void)
{
	int			i;
	static char	bar[500];
	const char	*lable;
	char		*someonesmom;

	someonesmom = "███████████████████████";
	i = 0;
	lable = "|/-\\";
	ft_memset(bar, 0, 102 * sizeof(char));
	printf("\e[36m \
              LOADING PLEASE WAIT ...\e[0m\n");
	while (i <= 100)
	{
		if (i % 3 == 0)
			ft_strlcpy(&bar[i], someonesmom, 500);
		printf("\r\e[4;35m\e[40m\e[1;98m%-2s\e[0m\e[36m [%d%%] [%c]", bar,
			i, lable[i % 4]);
		usleep(3000);
		fflush(stdout);
		i ++;
	}
	printf("\n");
}
