/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/28 21:32:26 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*collect_varname(char **iter, t_command_block *first)
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

char	*collect_varvalue(char *varname, t_command_block *first)
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
				command_blocks_fail_exit(first);
			return (varvalue);
		}
		env = env->next;
	}
	varvalue = ft_strdup("");
	if (varvalue == NULL)
		command_blocks_fail_exit(first);
	return (varvalue);
}

void	init_new_value(t_token *token, char *new_value)
{
	free (token->value);
	token->value = new_value;
}

void	expand_dollar_sign(char **iter, char **new_token_value, t_command_block *first)
{
	char	*varname;
	char	*varvalue;

	varname = collect_varname(iter, first);
	varvalue = collect_varvalue(varname, first);
	free(varname);
	*new_token_value = ft_strjoin_free(*new_token_value, varvalue);
	if (new_token_value == NULL)
		command_blocks_fail_exit(first);
}

bool	expander_quote_is_closed(char *iter)
{
	if (ft_strchr(iter + 1, *iter) != NULL)
		return (true);
	return (false);
}

void	expand_double_quotes(char **iter, char **new_token_value, t_command_block *first)
{
	(*iter)++;
	while (**iter != '"')
	{
		if (**iter == '$')
			expand_dollar_sign(iter, new_token_value, first);
		else
			expander_advance_with_char(iter, new_token_value, first);
	}
	(*iter)++;
}

void	expand_single_quotes(char **iter, char **new_token_value, t_command_block *first)
{
	(*iter)++;
	while (**iter != '\'')
	{
		expander_advance_with_char(iter, new_token_value, first);
	}
	(*iter)++;
}

void	expand_token(t_token *token, t_command_block *first)
{
	char	*iter;
	char	*new_token_value;

	new_token_value = ft_strdup("");
	if (new_token_value == NULL)
		command_blocks_fail_exit(first);
	iter = token->value;
	while (*iter != '\0')
	{
		if (*iter == EXPAND_DOUBLE_QUOTE && expander_quote_is_closed(iter))
			expand_double_quotes(&iter, &new_token_value, first);
		else if (*iter == EXPAND_SINGLE_QUOTE && expander_quote_is_closed(iter))
			expand_single_quotes(&iter, &new_token_value, first);
		else if (*iter == EXPAND_DOLLAR_SIGN)
			expand_dollar_sign(&iter, &new_token_value, first);
		else
			expander_advance_with_char(&iter, &new_token_value, first);
	}
	init_new_value(token, new_token_value);
}

void	expander(t_command_block *lexer)
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
				expand_token(i_token, lexer);
			i_token = i_token->next;
		}
		i_block = i_block->next;
	}
}

void	parser_expander(t_command_block *lexer)
{
	expander(lexer);
}
