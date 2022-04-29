/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:10:56 by shaas             #+#    #+#             */
/*   Updated: 2022/04/28 19:15:34 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <locale.h>

# include "../libft/libft.h"
# include "structs.h"
# include "env.h"
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "redir_creator.h"
# include "executor.h"
# include "builtins.h"

#endif
