/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:25:35 by pramella          #+#    #+#             */
/*   Updated: 2020/05/03 15:00:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define NULL_STR "(null)"

/*
** LIST FUNCTIONS
*/

typedef	struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstadd_front(t_list **alst, t_list *new);
void					ft_lstclear(t_list **lst, void (*del)(void*));
void					ft_lstdelone(t_list *lst, void (*del)(void*));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list					*ft_lstnew(void *content);
void					ft_lstrm(t_list **begin, t_list *prev, t_list *curr);
int						ft_lstsize(t_list *lst);

/*
** STANDARD FUNCTIONS
*/

int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t count, size_t size);

int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isinset(int c, char *set);
int						ft_isprint(int c);
int						ft_isspace(int c);

char					*ft_itoa(int n);

void					*ft_memccpy(void *dst, const void *src, int c,
						size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, int c, size_t len);

void					ft_putchar_fd(char c, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);

char					**ft_split(char const *s, char *charset);
int						ft_split_free(char **split);
char					*ft_strcat(char *dest, char *src);
char					*ft_strchr(const char *s, int c);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strdup(const char *src);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlen(const char *s);
char					*ft_strmapi(char const *s,
						char (*f) (unsigned int, char));
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char					*ft_strrchr(const char *s, int c);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_substr(char const *s, unsigned int start,
						size_t len);
int						ft_tolower(int c);
int						ft_toupper(int c);

/*
** GET_NEXT_LINE
*/

typedef struct			s_list_fd
{
	int					fd;
	int					ret;
	char				*buf;
	struct s_list_fd	*next;
}						t_list_fd;

int						get_next_line(int fd, char **line);
size_t					ft_strlen_gnl(const char *s);
char					*ft_strjoin_gnl(char const *s1, char const *s2);
char					*ft_cleanbuf_gnl(char *str);
void					ft_lstclear_gnl(int fd, t_list_fd **head);

/*
** FT_PRINTF
*/

typedef struct			s_fields
{
	int					zero_flag;
	int					left_flag;
	int					wd_flag;
	int					wd;
	int					prc_flag;
	int					prc_err_flag;
	int					prc;
	int					fd;
	char				type;
	size_t				end;
}						t_fields;

typedef struct			s_nbr
{
	long				value;
	int					unsigned_flag;
	int					len;
	char				*base;
}						t_nbr;

int						ft_printf(const char *fmt, ...)
 __attribute__((format(printf,1,2)));
t_fields				*ft_format_setup(char *fmt, va_list *ap);

void					ft_char_conv(t_fields *flags, va_list *ap, int *ret);
void					ft_str_conv(t_fields *flags, va_list *ap, int *ret);
void					ft_ptr_conv(t_fields *flags, va_list *ap, int *ret);
void					ft_mod_conv(t_fields *flags, int *ret);

void					ft_dec_conv(t_fields *flags, va_list *ap, int *ret);
void					ft_dec_helper(t_fields *flags, t_nbr *nbr);
void					ft_dec_relayer(t_fields *flags, t_nbr *nbr, int *ret);

void					ft_putnbr_base(long nbr, char *base, int base_len);
int						ft_nbr_base_size(long nbr, int base_len);
/*
** FT_FRINTF
*/

int						ft_fprintf(int fd, const char *fmt, ...)
 __attribute__((format(printf,2,3)));
t_fields				*ft_format_setup_fd(char *fmt, va_list *ap);

void					ft_char_conv_fd(t_fields *flags, va_list *ap, int *ret);
void					ft_str_conv_fd(t_fields *flags, va_list *ap, int *ret);
void					ft_ptr_conv_fd(t_fields *flags, va_list *ap, int *ret);
void					ft_mod_conv_fd(t_fields *flags, int *ret);

void					ft_dec_conv_fd(t_fields *flags, va_list *ap, int *ret);
void					ft_dec_helper_fd(t_fields *flags, t_nbr *nbr);
void					ft_dec_relayer_fd
						(t_fields *flags, t_nbr *nbr, int *ret);

void					ft_putnbr_base_fd
						(long nbr, char *base, int base_len, int fd);
int						ft_nbr_base_size_fd(long nbr, int base_len);

#endif
