/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:47:19 by satori            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/22 13:23:09 by mrojas-e         ###   ########.fr       */
=======
/*   Updated: 2022/04/21 22:10:54 by shaas            ###   ########.fr       */
>>>>>>> 4f6bffb7ef9206d1aebfaef31d7ece5e99f2396f
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_error(char *msg, int exit_status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	g_exit_status = exit_status;
	return (true);
}
