/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:10:36 by shaas             #+#    #+#             */
/*   Updated: 2022/04/26 20:57:48 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* >============EXECUTOR===============< */

void	executor(t_exec_block *exec_blocks);
void	execute_cmd(char *cmd_path, t_exec_block *i_exec, t_exec_block *exec_blocks);
void	executor_fail_exit(t_exec_block *exec_blocks);
bool	is_inbuilt(t_exec_block *i_exec);
void	handle_inbuilt(t_exec_block *i_exec, t_exec_block *exec_blocks);
char	*find_cmd_path(char *cmd, t_exec_block *exec_blocks);
char	**prepare_paths(t_exec_block *exec_blocks);
char	**combine_paths_and_cmd(char *cmd, char **paths, t_exec_block *exec_blocks);
char	*check_paths(char **paths, t_exec_block *exec_blocks);
char	*error_cmd_not_found(char *cmd);

#endif
