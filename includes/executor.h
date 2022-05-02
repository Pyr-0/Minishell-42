/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:10:36 by shaas             #+#    #+#             */
/*   Updated: 2022/05/02 21:52:53 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* >============EXECUTOR===============< */

void	executor(t_exec_block *exec_blocks);
bool	executor_loop(t_exec_block *exec_blocks, int *child_process_num);
void	prepare_for_next_loop(int *tmp_in, int pp[2]);
void	congfigure_fds(int pp[2], int fds_to_use[2],
			int tmp_in, t_exec_block *i_exec);
void	executor_fail_exit(t_exec_block *exec_blocks);

/* >============HANDLE INBUILTS===============< */
bool	is_inbuilt(t_exec_block *i_exec);
void	handle_inbuilt(int fds_to_use[2], t_exec_block *i_exec,
			t_exec_block *exec_blocks);

/* >============HANDLE NON INBUILTS===============< */
bool	handle_non_inbuilt(int fds_to_use[2], t_exec_block *i_exec,
							t_exec_block *exec_blocks, int *child_process_num, int tmp_in, int pp[2]);
void	execute_cmd(int fds_to_use[2], char *cmd_path, t_exec_block *i_exec,
						t_exec_block *exec_blocks, int tmp_in, int pp[2]);

/* >============FIND CMD PATH===============< */
char	*find_cmd_path(char *cmd, t_exec_block *exec_blocks);
char	**prepare_paths(t_exec_block *exec_blocks);
char	**combine_paths_and_cmd(char *cmd, char **paths,
			t_exec_block *exec_blocks);
char	*check_paths(char **paths, t_exec_block *exec_blocks);
char	*error_cmd_not_found(char *cmd);

/* >============ARGV/ENVP CREATOR===============< */
char	**argv_creator(t_exec_block *i_exec, t_exec_block *exec_blocks);
int		env_counter(void);
char	*env_helper(t_env *curr_env, t_exec_block *exec_blocks);
char	**envp_creator(t_exec_block *exec_blocks);

#endif
