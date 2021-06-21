/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:29:20 by kgale             #+#    #+#             */
/*   Updated: 2021/04/27 16:20:02 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_buff
{
	char			*content;
	int				fd;
	struct s_buff	*next;
	int				end;
}					t_buff;

int					ft_write_in_line(char **line, char *content);
int					ft_find_end_line_in_buff(char *str, t_buff **lst, int fd);
int					ft_ret(char ***line, t_buff **currelem,
						int fd, t_buff **lst);
void				find_curr(t_buff *curr, int fd, t_buff **lst);
int					ft_init(int *flag, int fd, char buff[2]);
void				ft_empty(int *flag, char **dest);
int					my_strlen(const char *str);
int					get_next_line(const int fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2);
char				*my_strjoin(char const *s1, char const *s2);
t_buff				*ft_lstadd_bck(t_buff **lst,
						char *content, int len, int fd);
int					ft_strlen(const char *str);
void				ft_strlcpy(char **dst, const char *src, int siz, int index);
int					ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcpy(char *dest, const char *src);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t siz);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big,
						const char *little, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_aredigits(char *s);
char				**my_split(char const *s);
int					define(int *in, char const *s, char c, int *words);
int					ft_find_word_start(int index, char const *s, char c);
int					f(int index, char const *s, char c);
#endif
