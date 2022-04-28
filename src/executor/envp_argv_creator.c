/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_argv_creator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:24:29 by shaas             #+#    #+#             */
/*   Updated: 2022/04/28 18:24:56 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**argv_creator(t_exec_block *i_exec, t_exec_block *exec_blocks)
{
	char	**argv;
	t_arg	*i_arg;
	int		argc;
	int		i;

	argc = 1;
	i_arg = i_exec->arg;
	while (i_arg != NULL)
	{
		argc++;
		i_arg = i_arg->next;
	}
	argv = malloc((argc + 1) * sizeof(char *));
	if (argv == NULL)
		executor_fail_exit(exec_blocks);
	argv[0] = i_exec->cmd;
	i = 0;
	i_arg = i_exec->arg;
	while (++i < argc)
	{
		argv[i] = i_arg->value;
		i_arg = i_arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	env_counter(void)
{
	t_env	*i_env;
	int		envc;

	i_env = *(get_env(NULL));
	envc = 0;
	while (i_env != NULL)
	{
		envc++;
		i_env = i_env->next;
	}
	return (envc);
}

char	*env_helper(t_env *curr_env, t_exec_block *exec_blocks)
{
	char	*curr_envp;
	char	*buf;

	curr_envp = ft_strjoin(curr_env->varname, "=");
	if (curr_envp == NULL)
		executor_fail_exit(exec_blocks);
	buf = curr_envp;
	curr_envp = ft_strjoin(curr_envp, curr_env->varvalue);
	free (buf);
	if (curr_envp == NULL)
		executor_fail_exit(exec_blocks);
	return (curr_envp);
}

char	**envp_creator(t_exec_block *exec_blocks)
{
	char	**envp;
	t_env	*env;
	int		envc;
	int		i;

	envc = env_counter();
	envp = malloc((envc + 1) * sizeof(char *));
	if (envp == NULL)
		executor_fail_exit(exec_blocks);
	i = 0;
	env = *(get_env(NULL));
	while (i < envc)
	{
		envp[i] = env_helper(env, exec_blocks);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
