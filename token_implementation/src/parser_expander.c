/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/25 22:00:40 by mrojas-e         ###   ########.fr       */
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

	varname = NULL;
	while (**iter != ' ' && **iter != '\0')
	{
		if (is_in_double_quotes == true && **iter == '"')
			break ;
		c = expander_get_current_char_as_string(**iter);
		varname = ft_strjoin_free(varname, c);
		(*iter)++;
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

void	replace_dollar_sign(char *varvalue, char **iter, t_token *token)
{
	char	*new_value;
	char	*new_iter;
	char	*varvalue_alloc;
	char	*c;

	new_value = NULL;
	new_iter = token->value;
	varvalue_alloc = ft_strdup(varvalue);
	while (new_iter++ != *iter)
	{
		c = expander_get_current_char_as_string(*new_iter);
		new_value = ft_strjoin_free(new_value, c);
	}
	new_value = ft_strjoin_free(new_value, varvalue_alloc);
	while (*new_iter != ' ' && *new_iter != '\0')
		new_iter++;
	while (*new_iter != '\0')
	{
		c = expander_get_current_char_as_string(*new_iter);
		new_value = ft_strjoin_free(new_value, c);
		new_iter++;
	}
	free (token->value);
	token->value = new_value;
	*iter = new_value;
}

void	expand_dollar_sign(char **iter, t_token *token, t_env *env, bool is_in_double_quotes)
{
	char	*varname;
	char	*varvalue;

	varname = collect_varname(iter, is_in_double_quotes);
	varvalue = collect_varvalue(env, varname);
	free(varname);
	replace_dollar_sign(varvalue, iter, token);
}

void	expand_token(t_token *token, t_command_block *lexer, t_env *env)
{
	char	*iter;

	(void)lexer;
	iter = token->value;
	while (iter != '\0')
	{
		//if (*iter == EXPAND_DOUBLE_QUOTE)
//
		//if (*iter == EXPAND_SINGLE_QUOTE)
//
		if (*iter == EXPAND_DOLLAR_SIGN)
		{
			printf("here!!!!!!!\n");
			expand_dollar_sign(&iter, token, false, env);
		}
		else
			iter++;
	}
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