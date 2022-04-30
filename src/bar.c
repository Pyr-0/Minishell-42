/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bar.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:08:55 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/30 03:09:11 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void progress()
{
    int i = 0;
    char bar[102];
    memset(bar,0,102*sizeof(char));
    const char* lable="|/-\\";

    printf("\e[36m                                    LOADING PLEASE WAIT ...\e[0m\n");
    while(i <= 100)
    {
        bar[i] = '#';    
        //printf("\r\e[36m [%d%%] [%c]\n",i,lable[i%4]); line by line %
        printf("\r\e[4;35m\e[40m\e[1;98m[%-2s]\e[0m\e[36m [%d%%] [%c]",bar,i,lable[i%4]);
        usleep(19999);
    	fflush(stdout);
        i++;
    }
    printf("\n");
}
