# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 20:31:38 by ede-thom          #+#    #+#              #
#    Updated: 2019/12/11 22:48:18 by ede-thom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memccpy.c\
			ft_memmove.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strlen.c\
			ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strncmp.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_strnstr.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strtrim.c\
			ft_strjoin.c\
			ft_split.c\
			ft_split_charset.c\
			ft_itoa.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_strmapi.c
			
SRCS	+=	ft_atoi_base.c\
			ft_indexof.c\
			ft_iswhitespace.c\
			ft_max.c\
			ft_min.c\
			ft_swap.c\
			ft_pow.c

BONUS	=	ft_lstadd_front.c\
			ft_lstadd_back.c\
			ft_lstnew.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstiter.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstmap.c	

OBJS	=	${SRCS:.c=.o}

BOBJS	=	${BONUS:.c=.o}

NAME	=	libft.a

RED		=	\033[0;31m
GREEN	= 	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[0;36m
RESET	=	\033[0m

CFLAGS	=	-Wall -Wextra -Werror -I./

CC		=	gcc

RM		=	rm -f



all:		${NAME}

$(NAME):	${OBJS} ${BOBJS}
			@echo "$(CYAN)Done creating $(NAME) object files!            $(RESET)"
			@ar -crs ${NAME} ${OBJS} ${BOBJS}
			@echo "$(CYAN)Created $(GREEN)$(NAME)$(CYAN)!! $(RESET)"

%.o:		%.c libft.h
			@${CC} ${CFLAGS} -c $< -o $@
			@printf "$(CYAN)Compiling $(MAGENTA)$<$(RESET)\r"
clean: 
			@${RM} ${OBJS}
			@${RM} ${BOBJS}
			@echo "$(CYAN)$(NAME): clean $(RESET)"

bonus:		${OBJS} ${BOBJS}
			@echo "$(NAME): $(CYAN)DID SOME1 ORDER A $(YELLOW) BONUS $(CYAN)???$(RESET)"
			@ar -crs $(NAME) $(OBJS) $(BOBJS)
			@echo "$(CYAN)Sucesfully created $(YELLOW)bonus $(GREEN)$(NAME)$(RESET)"

fclean:		clean
			@${RM} ${NAME}
			@echo "$(CYAN)$(NAME): $(RED)f$(CYAN)clean $(RESET)"

re:			fclean all

test:		all
			${CC} tests.c -L./ -lft

.PHONY:	all clean fclean test re
