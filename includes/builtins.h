/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:14:35 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 18:55:47 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* >============BUILTINS===============< */

bool	cmd_echo(int fds_to_use[2], t_exec_block *echo);
bool	cmd_pwd(int fds_to_use[2], t_exec_block *cmd_pwd);
bool	cmd_cd(t_exec_block *cd);
bool	cmd_env(int fds_to_use[2], t_exec_block *cmd_env);
bool	cmd_export(int fds_to_use[2], t_exec_block *cmd_export);
bool	handle_error(char *msg, int exit_status);
char	*fetch_env_var_value(char *varname);
void	unset_variable(t_arg *varname);
bool	cmd_unset(t_exec_block *cmd_unset);
int		cmd_exit(t_exec_block *cmd_exit, t_exec_block *exec_blocks);

#endif
