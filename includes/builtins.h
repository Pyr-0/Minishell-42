/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:14:35 by shaas             #+#    #+#             */
/*   Updated: 2022/04/28 19:16:19 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* >============BUILTINS===============< */

bool	cmd_echo(t_exec_block *echo);
bool	cmd_pwd(t_exec_block *cmd_pwd);
bool	cmd_cd(t_exec_block *cd);
bool	cmd_env(t_exec_block *cmd_env);
bool	cmd_export(t_exec_block *cmd_export);
bool	handle_error(char *msg, int exit_status);
char	*fetch_env_var_value(char *varname);
void	unset_variable(t_arg *varname);
bool	cmd_unset(t_exec_block *cmd_unset);
int		cmd_exit(t_exec_block *cmd_exit, t_exec_block *exec_blocks);

#endif
