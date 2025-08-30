# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 04:27:27 by emetel            #+#    #+#              #
#    Updated: 2025/08/30 15:01:41 by emetel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g3

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	READLINE_DIR := $(shell brew --prefix readline 2>/dev/null)
	ifneq ($(READLINE_DIR),)
		CFLAGS += -I$(READLINE_DIR)/include
		LDFLAGS += -L$(READLINE_DIR)/lib
	endif
endif

SRCS =	minishell.c \
		expander.c \
		expand_quote.c \
		quote_utils.c \
		quote_processing.c \
		expand_utils.c \
		expand_utils2.c \
		expand_tilde.c \
		handle_redirection.c \
		parsing.c \
		segment_handler.c \
		segment.c \
		signal.c \
		token_utils.c \
		token_utils2.c \
		token_utils3.c \
		token_utils4.c \
		token.c \
		token_helpers.c \
		exec.c \
		exec2.c \
		exec_utils.c \
		exec_utils2.c \
		shlvl.c \
		synthax_detection.c \
		builtin/env_utils.c \
		builtin/env_lst.c \
		builtin/builtin.c \
		builtin/echo.c \
		builtin/pwd.c \
		builtin/cd.c \
		builtin/cd_utils.c \
		builtin/env.c \
		builtin/export.c \
		builtin/export_utils.c \
		builtin/export_utils2.c \
		builtin/export_utils3.c \
		builtin/unset.c \
		builtin/exit.c \
		redir.c \
		redir2.c \
		redir3.c \
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
	@$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS_PREF)
	@make all -C lib
	@$(CC) $(FLAGS) -lreadline $(LDFLAGS) $(OBJS_PREF) $(LIB_NAME) -o $(NAME)
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
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re valgrind