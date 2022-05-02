/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:01:36 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/02 16:03:28 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_heredoc_fail_exit(int *heredoc_pp)
{
	close(heredoc_pp[PIPE_READ]);
	close(heredoc_pp[PIPE_WRITE]);
}

bool	check_if_last_input_is_heredoc(t_parser_block *i_parser)
{
	t_redir	*i_redir;
	bool	last_input_is_heredoc;

	i_redir = i_parser->redir;
	last_input_is_heredoc = false;
	while (i_redir != NULL)
	{
		if (i_redir->e_redir_type == REDIR_INPUT_HEREDOC)
			last_input_is_heredoc = true;
		if (i_redir->e_redir_type == REDIR_INPUT_FILE)
			last_input_is_heredoc = false;
		i_redir = i_redir->next;
	}
	return (last_input_is_heredoc);
}
