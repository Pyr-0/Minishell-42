# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaas <shaas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 12:46:02 by mrojas-e          #+#    #+#              #
#    Updated: 2022/03/16 20:19:16 by shaas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	libft.a
COMP		=	gcc -Wall -Wextra -Werror -c
SRC			=	ft_isalnum.c\
				ft_atoi.c\
				ft_isalpha.c\
				ft_isdigit.c\
				ft_memmove.c\
				ft_memchr.c\
				ft_memset.c\
				ft_strlen.c\
				ft_tolower.c\
				ft_bzero.c\
				ft_isascii.c\
				ft_isprint.c\
				ft_memcpy.c\
				ft_memcmp.c\
				ft_strlcpy.c\
				ft_strncmp.c\
				ft_toupper.c\
				ft_strlcat.c\
				ft_strchr.c\
				ft_strrchr.c\
				ft_strnstr.c\
				ft_calloc.c\
				ft_strdup.c\
				ft_realloc.c\
				ft_substr.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_split.c\
				ft_itoa.c\
				ft_strmapi.c\
				ft_striteri.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c
OBJ			=	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(COMP) $< -o $@

$(NAME): $(OBJ)
	@printf $(LIGHTBLUE)"*--------libtft compiled!--------------*\n"$(RESET)
	@ar rc $(NAME) $(OBJ)
	@printf $(LIGHTBLUE)"*--------library created!--------------*\n"$(RESET)

clean: 
	@rm -fr $(OBJ)
	@printf $(LIGHTBLUE)"*--------libft object files removed!---*\n"$(RESET)

fclean: clean
	@rm -fr $(NAME)
	@printf $(LIGHTBLUE)"*--------$(NAME) removed!--------------*\n"$(RESET)

re: fclean all

# text modifiers #
RED = "\e[31m"

GREEN = "\e[32m"

YELLOW = "\e[33m"

BLUE = "\e[34m"

MAGENTA = "\e[35m"

CYAN = "\e[36m"

LIGHTGRAY = "\e[37m"

DARKGRAY = "\e[90m"

LIGHTRED = "\e[91m"

LIGHTGREEN = "\e[92m"

LIGHTYELLOW = "\e[93m"

LIGHTBLUE = "\e[94m"

LIGHTMAGENTA = "\e[95m"

LIGHTCYAN = "\e[96m"

RED_BG = "\e[41m"

GREEN_BG = "\e[42m"

YELLOW_BG = "\e[43m"

BLUE_BG = "\e[44m"

MAGENTA_BG = "\e[45m"

CYAN_BG = "\e[46m"

LIGHTGRAY_BG = "\e[47m"

DARKGRAY_BG = "\e[100m"

LIGHTRED_BG = "\e[101m"

LIGHTGREEN_BG = "\e[102m"

LIGHTYELLOW_BG = "\e[103m"

LIGHTBLUE_BG = "\e[104m"

LIGHTMAGENTA_BG = "\e[105m"

LIGHTCYAN_BG = "\e[106m"

BOLD = "\e[1m"

ITALIC = "\e[3m"

UNDERLINED = "\e[4m"

RESET = "\e[0m"
