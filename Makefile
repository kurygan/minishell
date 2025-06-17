# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 04:27:27 by emetel            #+#    #+#              #
#    Updated: 2025/06/17 22:36:21y mkettab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -I/opt/homebrew/opt/readline/include

SRCS =	minishell.c \
		gc/gc_malloc.c gc/gc_utils.c gc/gc_strdup.c \
		expander.c \
		handle_redirection.c \
		parsing.c \
		segment_handler.c \
		segment_options.c \
		segment.c \
		signal.c \
		token_utils.c \
		token.c \
		debug.c

SRCS_DIR = src/
OBJS_DIR = build/
SRCS_PREF = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS:.c=.o)
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS))

NAME = minishell
LIB_NAME = lib/lib.a

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS_PREF)
	@make -C lib
	@$(CC) $(FLAGS) -lreadline -L/opt/homebrew/opt/readline/lib $(OBJS_PREF) \
	$(LIB_NAME) -o $(NAME)
	@echo "|🛠️| Program compiled"

all: $(NAME)

clean:
	@make clean -C lib
	@rm -rf $(OBJS_DIR)
	@echo "|🗑️| Removing objects.."

fclean: clean
	@make fclean -C lib
	@rm -f $(NAME)
	@echo "|🧹| Cleaning.."

re: fclean all 

.PHONY: all clean fclean re