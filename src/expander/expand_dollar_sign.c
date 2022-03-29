/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:14:43 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 18:49:53 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*collect_varname(char **iter, t_lexer_block *first)
{
	char	*varname;

	varname = ft_strdup("");
	if (varname == NULL)
		return (NULL);
	(*iter)++;
	while (**iter != ' ' && **iter != '\0' && **iter != '$' && **iter != '\'' && **iter != '"')
	{
		expander_advance_with_char(iter, &varname, first);
	}
	return (varname);
}

char	*collect_varvalue(char *varname, t_lexer_block *first)
{
	char	*varvalue;
	t_env	*env;

	env = *get_env(NULL);
	while (env != NULL && varname != NULL)
	{
		if (ft_strncmp(env->varname, varname, INT_MAX) == 0)
		{
			varvalue = ft_strdup(env->varvalue);
			if (varvalue == NULL)
				lexer_blocks_fail_exit(first);
			return (varvalue);
		}
		env = env->next;
	}
	varvalue = ft_strdup("");
	if (varvalue == NULL)
		lexer_blocks_fail_exit(first);
	return (varvalue);
}

void	expand_dollar_sign(char **iter, char **new_token_value, t_lexer_block *first)
{
	char	*varname;
	char	*varvalue;

	varname = collect_varname(iter, first);
	varvalue = collect_varvalue(varname, first);
	free(varname);
	*new_token_value = ft_strjoin_free(*new_token_value, varvalue);
	if (new_token_value == NULL)
		lexer_blocks_fail_exit(first);
}
