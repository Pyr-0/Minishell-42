/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:08:55 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/03 16:24:19 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	progress_bar(void)
{
	int			i;
	static char	bar[500];
	const char	*lable;
	char		*someonesmom;

	someonesmom = "███████████████████████";
	i = 0;
	lable = "|/-\\";
	ft_memset(bar, 0, 102 * sizeof(char));
	printf("\e[0;90m \
                  LOADING PLEASE WAIT ...\e[0m\n");
	while (i <= 100)
	{
		if (i % 3 == 0)
			ft_strlcpy(&bar[i], someonesmom, 500);
		printf("\r\e[0;90m%-2s\e[0m\e[0;90m [%d%%] [%c]", bar,
			i, lable[i % 4]);
		usleep(5000);
		fflush(stdout);
		i ++;
	}
	printf("\n");
} */

void	logo(void)
{
	printf("\n\n\n");
	printf("      \e[93m           (        )       (     (              \n");
	printf("                 )\\ )  ( /(       )\\ )  )\\ )           \n");
	printf("             (  (()/(  )\\()) (   (()/( (()/( (         \n");
	printf("             )\\  /(_))((_)\\  )\\   /(_)) /(_)))\\        \n");
	printf("           '((_)(_))   _((_)((_) (_))  (_))  (_)       \n");
	printf("      \e[35m _ _   (_)/ __| | || || __|| |   | |   (_) _ _   \n");
	printf("      | '  \\ | |\\__ \\ | __ || _| | |__ | |__ | || ' \\  \n");
	printf("      |_|_|_||_||___/ |_||_||___||____||____||_||_||_| \n");
	printf("      \e[0;30m                            by shaas & mrojas-e  \n");
	printf("\e[0m");
	printf("\n\n\n");
}
