CC = cc
FLAGS = -Wall -Wextra -Werror -g3

SRCS = minishell.c
SRCS_DIR = src/
OBJS_DIR = build/
SRCS_PREF = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS:.c=.o)
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS))

NAME = minishell
LIB_NAME = lib/lib.a

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS_PREF)
	@make all -C lib
	@$(CC) $(FLAGS) $(OBJS_PREF) $(LIB_NAME) -lreadline -o $(NAME)
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