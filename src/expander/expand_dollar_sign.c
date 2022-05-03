/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:14:43 by shaas             #+#    #+#             */
/*   Updated: 2022/05/03 16:00:28 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*collect_varname(char **iter, t_lexer_block *first)
{
	char	*varname;

	(*iter)++;
	varname = ft_strdup("");
	if (varname == NULL)
		lexer_blocks_fail_exit(first);
	while (**iter != ' ' && **iter != '\0' && **iter
		!= '$' && **iter != '\'' && **iter != '"' && *(*iter - 1) != '?')
		expander_advance_with_char(iter, &varname, first);
	return (varname);
}

char	*collect_varvalue(char *varname)
{
	t_env	*env;

	if (varname[0] == '\0')
		return (ft_strdup("$"));
	if (varname[0] == '?')
		return (ft_itoa(g_exit_status));
	env = *get_env(NULL);
	while (env != NULL && varname != NULL)
	{
		if (ft_strncmp(env->varname, varname, INT_MAX) == 0)
		{
			if (env->varvalue == NULL)
				return (ft_strdup(""));
			return (ft_strdup(env->varvalue));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

void	expand_dollar_sign(char **iter, char **new_token_value,
						t_lexer_block *first)
{
	char	*varname;
	char	*varvalue;

	varname = collect_varname(iter, first);
	varvalue = collect_varvalue(varname);
	if (varvalue == NULL)
		lexer_blocks_fail_exit(first);
	free(varname);
	*new_token_value = ft_strjoin_free(*new_token_value, varvalue);
	if (new_token_value == NULL)
		lexer_blocks_fail_exit(first);
}
