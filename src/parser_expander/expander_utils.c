/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:13:28 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 18:17:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	expander_quote_is_closed(char *iter)
{
	if (ft_strchr(iter + 1, *iter) != NULL)
		return (true);
	return (false);
}

void	expander_init_new_value(t_token *token, char *new_value)
{
	free (token->value);
	token->value = new_value;
}

char	*expander_get_current_char_as_string(char c, t_command_block *first)
{
	char	*str;

	str = calloc(2, sizeof(char));
	if (str == NULL)
		command_blocks_fail_exit(first);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	expander_advance_with_char(char **iter, char **str, t_command_block *first)
{
	char	*c;

	c = expander_get_current_char_as_string(**iter, first);
	*str = ft_strjoin_free(*str, c);
	if (*str == NULL)
		command_blocks_fail_exit(first);
	(*iter)++;
}
