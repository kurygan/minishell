# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkettab <mkettab@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 04:27:27 by emetel            #+#    #+#              #
#    Updated: 2025/08/17 02:13:33 by mkettab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g3

SRCS =	minishell.c \
		expander.c \
		expand_quote.c \
		quote_utils.c \
		expand_utils.c \
		handle_redirection.c \
		parsing.c \
		segment_handler.c \
		segment_options.c \
		segment.c \
		signal.c \
		token_utils.c \
		token.c \
		exec.c \
		debug.c \
		builtin.c \
		redir.c \
		garbage_collector/gc_free.c \
		garbage_collector/gc_malloc.c \
		garbage_collector/gc_strdup.c \
		garbage_collector/gc_utils.c \
		garbage_collector/gc_substr.c \
		garbage_collector/gc_strjoin.c \
		garbage_collector/gc_itoa.c

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
	@make all -C lib
	@$(CC) $(FLAGS) -lreadline $(OBJS_PREF) $(LIB_NAME) -o $(NAME)
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

valgrind: $(NAME)
	@echo "|🔍| Running valgrind with readline suppression..."
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re valgrind