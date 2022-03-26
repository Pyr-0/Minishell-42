/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/26 02:17:20 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expander_get_current_char_as_string(char c)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*collect_varname(char **iter, bool is_in_double_quotes)
{
	char	*varname;
	char	*c;
	char	*iter2;

	varname = NULL;
	iter2 = (*iter) + 1;
	while (*iter2 != ' ' && *iter2 != '\0' && *iter2 != '$')
	{
		if (is_in_double_quotes == true && *iter2 == '"')
			break ;
		c = expander_get_current_char_as_string(*iter2);
		varname = ft_strjoin_free(varname, c);
		iter2++;
	}
	return (varname);
}

char	*collect_varvalue(t_env *env, char *varname)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->varname, varname, INT_MAX) == 0)
			return (env->varvalue);
		env = env->next;
	}
	return (NULL);
}

void	init_new_value(t_token *token, char *new_value, char **iter)
{
	free (token->value);
	token->value = new_value;
	*iter = new_value;
}

void	replace_dollar_sign_full_token(char *varvalue, char **iter, t_token *token)
{
	char	*new_value;
	char	*iter2;
	char	*varvalue_alloc;
	char	*c;

	new_value = NULL;
	iter2 = token->value;
	varvalue_alloc = ft_strdup(varvalue);
	while (iter2 != *iter)
	{
		c = expander_get_current_char_as_string(*iter2);
		new_value = ft_strjoin_free(new_value, c);
		iter2++;
	}
	iter2++;
	new_value = ft_strjoin_free(new_value, varvalue_alloc);
	while (*iter2 != ' ' && *iter2 != '\0' && *iter2 != '$')
		iter2++;
	while (*iter2 != '\0')
	{
		c = expander_get_current_char_as_string(*iter2);
		new_value = ft_strjoin_free(new_value, c);
		iter2++;
	}
	init_new_value(token, new_value, iter);
}

char	*expand_dollar_sign(char **iter, t_token *token, t_env *env, bool is_in_double_quotes)
{
	char	*varname;
	char	*varvalue;

	varname = collect_varname(iter, is_in_double_quotes);
	varvalue = collect_varvalue(env, varname);
	free(varname);
	if (is_in_double_quotes)
		return (ft_strdup(varvalue));
	replace_dollar_sign_full_token(varvalue, iter, token);
	return (NULL);
}

bool	expander_quote_is_closed(char *iter)
{
	if (ft_strchr(iter + 1, *iter) != NULL)
		return (true);
	return (false);
}

void	expand_double_quotes(char **iter, t_token *token, t_env *env)
{
	new_value = NULL;
	while (**iter != '"')
	{
		if (**iter == )
	}
	free (token, new_value, iter)
}

void	skip_single_quotes(char **iter)
{
	while (**iter != '\'')
		*iter++;
	*iter++;
}

void	expand_token(t_token *token, t_env *env)
{
	char	*iter;

	iter = token->value;
	while (iter != NULL && *iter != '\0')
	{
		if (*iter == EXPAND_DOUBLE_QUOTE && expander_quote_is_closed(iter));
			expand_double_quotes(&iter, token, env);
		else if (*iter == EXPAND_SINGLE_QUOTE && expander_quote_is_closed(iter))
			skip_single_quotes(&iter);
		else if (*iter == EXPAND_DOLLAR_SIGN)
			expand_dollar_sign(&iter, token, env, false);
		else
			iter++;
	}
	printf("\e[93m%s\e[0m\n", token->value);
	//if (tokewn) // if token is empty
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
			if (i_token->type == TOKEN_ID)
				expand_token(i_token, lexer, env);
			i_token = i_token->next;
		}
		i_block = i_block->next;
	}
}

void	parser_expander(t_command_block *lexer, t_env *env)
{
	expander(lexer, env);
}
