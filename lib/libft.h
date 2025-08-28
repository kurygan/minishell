/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emetel <emetel@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:08:04 by mkettab           #+#    #+#             */
/*   Updated: 2025/08/28 22:06:14 by emetel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdbool.h>

size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
char				*ft_strchr(const char *s, int c);
int					ft_atoi(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strcpy(char *dest, const char *src);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strrchr(const char *s, int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putint_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strcmp(char *s1, char *s2);
void				ft_freetab(char **str);

// Bonus Part

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				*get_next_line(int fd);
t_list				*ft_getlast(t_list *list);
int					ft_foundline(t_list *list);
int					read_and_stock(t_list **buf, int fd);
void				lst_clean(t_list **buf);
void				get_line_appart(t_list *buf, char **str);
void				stock_add(char *str, t_list **buf, int readed);
void				line_gen(char **str, t_list *buf);
void				lst_free(t_list *lst);

int					ft_intlen(long j);
long long			ft_atoll(char const *str, bool *error);
int					ft_putchar(char c);
int					ft_inthexlen(unsigned long c);
int					ft_putint(long d);
int					ft_putstr(char *str);
int					ft_intunslen(long c);
int					ft_putunsint(long d);
int					ft_puthex(unsigned long c, int low);
int					ft_putptr(void *ptr);
int					ft_printf(const char *s, ...);

#endif
