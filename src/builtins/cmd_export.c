/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:02:58 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/20 17:34:30 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cmd_export(t_env *cmd_export)
{
	char *str;
	
	init_env_node(str, cmd_export);
}


void	print_export(t_env *list)
{
	t_env	*new;
	t_env	*tmp;

	new = get_env(list);
	while (new)
	{
		write(1, "declare -x ", 11);
		ft_fprintf(1, "%s", new->varname);
		if (new->type == ENV_VAR)
			ft_fprintf(1, "=\"%s\" ", new->varvalue);
		write(1, "\n", 1);
		tmp = new;
		new = new->next;
		free(tmp);
	}
}
