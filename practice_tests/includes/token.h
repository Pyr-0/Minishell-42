/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:08:04 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/12 13:00:16 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum
	{
		TOKEN_ID, //metacharachter
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_BIGGER,
		TOKEN_REDIR_LEFT,
		TOKEN_REDIR_RIGHT,
		TOKEN_SMALLER
	}	type;

	char *value;
}	t_token;

t_token *init_token(int type, char *value);

#endif