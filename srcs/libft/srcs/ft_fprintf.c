/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:06:48 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:23:49 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parser(char *fmt, va_list *ap, int *ret, int fd)
{
	t_fields	*flags;
	int			i;

	if (!(ft_strchr("-*.0123456789cspdiuxX%", fmt[0])) || !fmt[0])
		return (1);
	if (!(flags = ft_format_setup_fd(fmt, ap)))
		return (-1);
	flags->fd = fd;
	(flags->type != 'c') ? 1 : ft_char_conv_fd(flags, ap, ret);
	(flags->type != 's') ? 1 : ft_str_conv_fd(flags, ap, ret);
	(flags->type != 'p') ? 1 : ft_ptr_conv_fd(flags, ap, ret);
	(flags->type != '%') ? 1 : ft_mod_conv_fd(flags, ret);
	(flags->type != 'd') ? 1 : ft_dec_conv_fd(flags, ap, ret);
	(flags->type != 'i') ? 1 : ft_dec_conv_fd(flags, ap, ret);
	(flags->type != 'u') ? 1 : ft_dec_conv_fd(flags, ap, ret);
	(flags->type != 'x') ? 1 : ft_dec_conv_fd(flags, ap, ret);
	(flags->type != 'X') ? 1 : ft_dec_conv_fd(flags, ap, ret);
	i = flags->end + 1;
	free(flags);
	flags = NULL;
	return (i);
}

int			ft_fprintf(int fd, const char *fmt, ...)
{
	int		i;
	int		j;
	int		ret;
	va_list	ap;
	char	*f;

	i = 0;
	ret = 0;
	va_start(ap, fmt);
	f = (char *)fmt;
	fd = (fd < 0) ? 1 : fd;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			if ((j = ft_parser(f + i + 1, &ap, &ret, fd)) == -1)
				return (-1);
			i += j;
		}
		else
			ret += write(fd, &fmt[i++], 1);
	}
	va_end(ap);
	return (ret);
}
