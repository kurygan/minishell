CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = str/ft_strnstr.c \
	   str/ft_strncmp.c \
	   str/ft_strchr.c \
	   str/ft_toupper.c \
	   str/ft_tolower.c \
	   str/ft_strlen.c \
	   str/ft_strlcpy.c \
	   str/ft_strdup.c \
	   str/ft_strlcat.c \
	   str/ft_strrchr.c \
	   str/ft_putchar_fd.c \
	   str/ft_putstr_fd.c \
	   str/ft_putendl_fd.c \
	   str/ft_substr.c \
	   str/ft_strjoin.c \
	   str/ft_strjoin_free.c \
	   str/ft_strtrim.c \
	   str/ft_itoa.c \
	   str/ft_split.c \
	   str/ft_strmapi.c \
	   str/ft_striteri.c \
	   str/ft_freetab.c \
	   str/ft_strcmp.c \
	   str/ft_strcpy.c \
	   num/ft_atoi.c \
	   num/ft_putint_fd.c \
	   num/ft_atoll.c \
	   is/ft_isascii.c \
	   is/ft_isprint.c \
	   is/ft_isdigit.c \
	   is/ft_isalnum.c \
	   is/ft_isalpha.c \
	   mem/ft_memset.c \
	   mem/ft_memchr.c \
	   mem/ft_memcmp.c \
	   mem/ft_bzero.c \
	   mem/ft_memcpy.c \
	   mem/ft_memmove.c \
	   mem/ft_calloc.c \
	   lst/ft_lstnew.c \
	   lst/ft_lstadd_front.c \
	   lst/ft_lstsize.c \
	   lst/ft_lstlast.c \
	   lst/ft_lstadd_back.c \
	   lst/ft_lstdelone.c \
	   lst/ft_lstclear.c \
	   lst/ft_lstiter.c \
	   lst/ft_lstmap.c \
	   printf/ft_printf_utils.c \
	   printf/ft_printf.c \
	   printf/ft_printint.c \
	   printf/ft_printstr.c \
	   gnl/get_next_line_utils.c \
	   gnl/get_next_line.c

OBJS = $(SRCS:.c=.o)

NAME = lib.a

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Archive Compiled"
	@ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@echo "Removing objects.."

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaning.."

re: fclean all

.PHONY: re fclean clean bonus all