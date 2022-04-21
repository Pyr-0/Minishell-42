/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:19 by satori            #+#    #+#             */
/*   Updated: 2022/04/21 22:10:54 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_error(char *msg, int exit_status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit_status = exit_status;
	return (true);
}

