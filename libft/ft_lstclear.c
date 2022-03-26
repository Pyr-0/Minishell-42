/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:33:38 by mrojas-e          #+#    #+#             */
/*   Updated: 2021/10/17 18:10:47 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*helper;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		helper = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = helper;
	}
	*lst = NULL;
}
