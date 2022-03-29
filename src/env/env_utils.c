/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:23:58 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 15:24:15 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_get_current_char_as_string(char c, t_env *first)
{
	char	*str;

	str = calloc(2, sizeof(char));
	if (str == NULL)
		env_fail_exit(first);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
