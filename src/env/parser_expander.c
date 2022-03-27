/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/27 17:53:19 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expander_get_current_char_as_string(char c)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	expander_advance_with_char(char **iter, char **str)
{
	char	*c;

	c = expander_get_current_char_as_string(**iter);
	*str = ft_strjoin_free(*str, c);
	(*iter)++;
}

char	*collect_varname(char **iter)
{
	char	*varname;

	varname = NULL;
	(*iter)++;
	while (**iter != ' ' && **iter != '\0' && **iter != '$' && **iter != '\'' && **iter != '"')
	{
		expander_advance_with_char(iter, &varname);
	}
	return (varname);
}

char	*collect_varvalue(t_env *env, char *varname)
{
	while (env != NULL && varname != NULL)
	{
		if (ft_strncmp(env->varname, varname, INT_MAX) == 0)
			return (env->varvalue);
		env = env->next;
	}
	return (NULL);
}

void	init_new_value(t_token *token, char *new_value)
{
	free (token->value);
	token->value = new_value;
}

void	expand_dollar_sign(char **iter, char **new_token_value, t_env *env)
{
	char	*varname;
	char	*varvalue;

	varname = collect_varname(iter);
	varvalue = collect_varvalue(env, varname);
	free(varname);
	*new_token_value = ft_strjoin_free(*new_token_value, ft_strdup(varvalue));
}

bool	expander_quote_is_closed(char *iter)
{
	if (ft_strchr(iter + 1, *iter) != NULL)
		return (true);
	return (false);
}

void	expand_double_quotes(char **iter, char **new_token_value, t_env *env)
{
	(*iter)++;
	while (**iter != '"')
	{
		if (**iter == '$')
			expand_dollar_sign(iter, new_token_value, env);
		else
			expander_advance_with_char(iter, new_token_value);
	}
	(*iter)++;
}

void	expand_single_quotes(char **iter, char **new_token_value)
{
	(*iter)++;
	while (**iter != '\'')
	{
		expander_advance_with_char(iter, new_token_value);
	}
	(*iter)++;
}

void	expand_token(t_token *token, t_env *env)
{
	char	*iter;
	char	*new_token_value;

	new_token_value = NULL;
	iter = token->value;
	printf("\e[36mhuh\e[0m\n");
	while (*iter != '\0')
	{
		if (*iter == EXPAND_DOUBLE_QUOTE && expander_quote_is_closed(iter))
			expand_double_quotes(&iter, &new_token_value, env);
		else if (*iter == EXPAND_SINGLE_QUOTE && expander_quote_is_closed(iter))
			expand_single_quotes(&iter, &new_token_value);
		else if (*iter == EXPAND_DOLLAR_SIGN)
			expand_dollar_sign(&iter, &new_token_value, env);
		else
			expander_advance_with_char(&iter, &new_token_value);
	}
	init_new_value(token, new_token_value);
}

void	expander(t_command_block *lexer, t_env *env)
{
	t_command_block	*i_block;
	t_token			*i_token;

	i_block = lexer;
	while (i_block != NULL)
	{
		i_token = i_block->tokens;
		while (i_token != NULL)
		{
			if (i_token->e_type == TOKEN_ID)
				expand_token(i_token, env);
			i_token = i_token->next;
		}
		i_block = i_block->next;
	}
}

void	parser_expander(t_command_block *lexer, t_env *env)
{
	expander(lexer, env);
}
