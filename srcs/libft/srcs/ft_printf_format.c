/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:32:20 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 22:32:21 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_flags_setup(char *format, t_fields *flags)
{
	size_t i;

	i = 0;
	while (ft_strchr("0-", format[i]) && format[i])
	{
		if (format[i] == '-')
		{
			flags->zero_flag = -1;
			flags->left_flag = 1;
		}
		else if (format[i] == '0' && flags->left_flag == -1)
			flags->zero_flag = 1;
		++i;
	}
	return (i);
}

static size_t	ft_width_setup(char *format, t_fields *flags, va_list *ap)
{
	size_t i;

	i = 0;
	while ((ft_isdigit(format[i]) || format[i] == '*') && format[i])
	{
		if (format[i] == '*')
		{
			flags->wd_flag = 0;
			flags->wd = va_arg(*ap, int);
		}
		else if (ft_isdigit(format[i]))
		{
			if (flags->wd == -1 || flags->wd_flag == 0)
			{
				flags->wd_flag = 1;
				flags->wd = 0;
			}
			flags->wd = flags->wd * 10 + format[i] - 48;
		}
		++i;
	}
	return (i);
}

static size_t	ft_precision_setup(char *format, t_fields *flags, va_list *ap)
{
	size_t i;

	i = 0;
	if (format[i] != '.')
		return (0);
	flags->prc_flag = ++i;
	while ((ft_isdigit(format[i]) || format[i] == '*') && format[i])
	{
		if (format[i] == '*')
		{
			flags->prc_flag = 0;
			flags->prc = va_arg(*ap, int);
		}
		else if (ft_isdigit(format[i]))
		{
			if (flags->prc == -1 || flags->prc_flag == 0)
			{
				flags->prc_flag = 1;
				flags->prc = 0;
			}
			flags->prc = flags->prc * 10 + format[i] - 48;
		}
		++i;
	}
	return (i);
}

static void		ft_check_format(t_fields *flags)
{
	if (flags->prc_flag == 1 && flags->prc == -1)
		flags->prc_err_flag = 1;
	if (flags->prc_flag != -1 && flags->prc < 0 && flags->prc_err_flag != 1)
	{
		flags->prc_flag = -1;
		flags->prc = -1;
	}
	if (flags->wd_flag == 0)
		flags->wd_flag = 1;
	if (flags->wd < 0 && flags->wd_flag == 1)
	{
		flags->left_flag = 1;
		flags->wd_flag = 1;
		flags->wd *= -1;
	}
}

t_fields		*ft_format_setup(char *format, va_list *ap)
{
	size_t		i;
	t_fields	*flags;

	i = 0;
	if (!(flags = malloc(sizeof(*flags))))
		return (NULL);
	flags->zero_flag = -1;
	flags->left_flag = -1;
	flags->wd_flag = -1;
	flags->wd = -1;
	flags->prc_flag = -1;
	flags->prc_err_flag = -1;
	flags->prc = -1;
	i = ft_flags_setup(format, flags);
	i += ft_width_setup(format + i, flags, ap);
	i += ft_precision_setup(format + i, flags, ap);
	flags->type = format[i];
	flags->end = ++i;
	ft_check_format(flags);
	return (flags);
}
