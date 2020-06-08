# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 02:26:02 by pminne            #+#    #+#              #
#    Updated: 2020/06/08 18:47:51 by pramella         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS_D	=	srcs/

SRCS	=	$(SRCS_D)minishell.c\
			$(SRCS_D)parsing/parsing.c\
			$(SRCS_D)parsing/envvar.c\
			$(SRCS_D)parsing/redirection.c\
			$(SRCS_D)parsing/cleaning.c\
			$(SRCS_D)parsing/syntax.c\
			$(SRCS_D)parsing/utils.c\
			$(SRCS_D)execution/execution.c\
			$(SRCS_D)execution/execve.c\
			$(SRCS_D)execution/set_fd_pipe.c\
			$(SRCS_D)execution/set_fd_redirect.c\
			$(SRCS_D)execution/utils.c\
			$(SRCS_D)builtin/cd.c\
			$(SRCS_D)builtin/echo.c\
			$(SRCS_D)builtin/env.c\
			$(SRCS_D)builtin/exit.c\
			$(SRCS_D)builtin/export.c\
			$(SRCS_D)builtin/pwd.c\
			$(SRCS_D)builtin/unset.c\
			$(SRCS_D)history/history.c\
			$(SRCS_D)history/dllst_utils.c\
			$(SRCS_D)signal/signal.c\
			$(SRCS_D)terminal/backspace.c\
			$(SRCS_D)terminal/edit_line.c\
			$(SRCS_D)terminal/get_next_line.c\
			$(SRCS_D)terminal/get_next_line_utils.c\
			$(SRCS_D)terminal/init_terminal.c\
			$(SRCS_D)terminal/keys_right_left.c\
			$(SRCS_D)terminal/keys_up_down.c\
			$(SRCS_D)terminal/prompt.c\
			$(SRCS_D)terminal/utils.c\
			$(SRCS_D)terminal/utils2.c\
			$(SRCS_D)utils/free.c\
			$(SRCS_D)utils/list_cmd.c\
			$(SRCS_D)utils/list_env.c\
			$(SRCS_D)utils/list_token.c\
			$(SRCS_D)utils/var_declaration.c\

OBJS	=	$(SRCS:.c=.o)

HEADER	=	$(SRCS_D)minishell.h

CC		=	clang

CFLAGS	=	-I$(SRCS_D) -Wall -Wextra -Werror

%.o:	%.c $(HEADER)
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: 	$(NAME)

$(NAME):$(OBJS) Makefile
		@make -C $(SRCS_D)libft/
		@echo "libft compilation done..."
		@$(CC) $(CFLAGS) -O3 -o $(NAME) $(OBJS) -lcurses -L$(SRCS_D)libft/ -lft
		@echo "minishell compilation done..."
		@echo "all your base are belong to us"

clean:
		@rm -rf $(OBJS)
		@rm -rf $(HOME)/.history
		@make clean -C $(SRCS_D)libft/
		@echo "make clean done..."

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(SRCS_D)libft/
		@echo "make fclean done..."

re:		fclean all

.PHONY: all fclean clean re
