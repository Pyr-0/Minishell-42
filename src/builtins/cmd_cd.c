/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:09:22 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/03 16:23:51 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_old_pwd_with_pwd(t_env **env, t_env *pwd)
{
	t_env	*iter;

	iter = *env;
	while (iter->next != NULL)
	{
		if (ft_strcmp(iter->varname, "OLDPWD") == 0)
		{
			free(iter->varvalue);
			iter->varvalue = pwd->varvalue;
			return ;
		}
		iter = iter->next;
	}
}

static void	set_env_pwd(void)
{
	t_env	**env;
	t_env	*iter;
	char	*cwd;

	env = get_env(NULL);
	iter = *env;
	while (iter->next != NULL)
	{
		if (ft_strcmp(iter->varname, "PWD") == 0)
		{
			cwd = getcwd(NULL, 0);
			if (cwd == NULL)
			{
				handle_error(
					"\e[46m\e[1;91mMi[shell]in: cd: no, this ain't right 🤥\e[0m\n",
					EXIT_STD_ERROR);
				return ;
			}
			replace_old_pwd_with_pwd(env, iter);
			iter->varvalue = cwd;
			return ;
		}
		iter = iter->next;
	}
}

bool	cmd_cd(t_exec_block *cd)
{
	int		res;

	res = 0;
	if (cd->arg == NULL)
		res = chdir(fetch_env_var_value("HOME"));
	else if (cd->arg->next != NULL)
		return (handle_error(
				"\e[1;91mMi[shell]in: cd: toooo much too handle 😥 \e[0m\n",
				EXIT_STD_ERROR));
	else
		res = chdir(cd->arg->value);
	if (res == -1)
		return (handle_error("\e[1;91mMi[shell]in: \
cd: whatcha' lookin' for here Darlin' 🤨\e[0m\n", EXIT_STD_ERROR));
	set_env_pwd();
	g_exit_status = EXIT_SUCCESS;
	return (false);
}
