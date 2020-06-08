/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:32:38 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 22:32:39 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parser(char *fmt, va_list *ap, int *ret)
{
	t_fields	*flags;
	int			i;

	if (!(ft_strchr("-*.0123456789cspdiuxX%", fmt[0])) || !fmt[0])
		return (1);
	if (!(flags = ft_format_setup(fmt, ap)))
		return (-1);
	(flags->type != 'c') ? 1 : ft_char_conv(flags, ap, ret);
	(flags->type != 's') ? 1 : ft_str_conv(flags, ap, ret);
	(flags->type != 'p') ? 1 : ft_ptr_conv(flags, ap, ret);
	(flags->type != '%') ? 1 : ft_mod_conv(flags, ret);
	(flags->type != 'd') ? 1 : ft_dec_conv(flags, ap, ret);
	(flags->type != 'i') ? 1 : ft_dec_conv(flags, ap, ret);
	(flags->type != 'u') ? 1 : ft_dec_conv(flags, ap, ret);
	(flags->type != 'x') ? 1 : ft_dec_conv(flags, ap, ret);
	(flags->type != 'X') ? 1 : ft_dec_conv(flags, ap, ret);
	i = flags->end + 1;
	free(flags);
	flags = NULL;
	return (i);
}

int			ft_printf(const char *fmt, ...)
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
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			if ((j = ft_parser(f + i + 1, &ap, &ret)) == -1)
				return (-1);
			i += j;
		}
		else
			ret += write(1, &fmt[i++], 1);
	}
	va_end(ap);
	return (ret);
}
