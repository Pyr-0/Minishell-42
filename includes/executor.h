/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:10:36 by shaas             #+#    #+#             */
/*   Updated: 2022/04/25 20:41:01 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* >============EXECUTOR===============< */

void	executor(t_exec_block *exec_blocks);
bool	is_inbuilt(t_exec_block *i_exec);
void	handle_inbuilt(t_exec_block *i_exec, t_exec_block *exec_blocks);

#endif
