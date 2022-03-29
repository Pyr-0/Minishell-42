/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:29:39 by shaas             #+#    #+#             */
/*   Updated: 2022/03/29 15:30:15 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*============ENV=============*/

t_env	**get_env(char *envp[]);
t_env	*init_env(char *envp[]);
t_env	*add_env_node(char *env_str, t_env *prev, t_env *first);
t_env	*init_env_node(char *env_str, t_env *first);
char	*env_get_current_char_as_string(char c, t_env *first);
char	*get_varvalue(char *env_str, t_env *first);
char	*get_varname(char *env_str, t_env *first);
void	env_fail_exit(t_env *env);
void	free_env(void);

#endif
