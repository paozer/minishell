/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_right_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:45:08 by pminne            #+#    #+#             */
/*   Updated: 2020/06/08 18:47:01 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_key_left(t_all *gbl, char *buf)
{
	if (gbl->spc->s == 0)
		return ;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
	{
		ft_putstr_fd(buf, 0);
		gbl->spc->s--;
	}
}

void	display_right(int i, char **line)
{
	char *s;

	s = *line;
	while (s[i])
	{
		write(1, s + i, 1);
		++i;
	}
}

void	check_key_right(t_all *gbl, char *buf, char **line)
{
	if (!*line || gbl->spc->s == ft_strlen(*line))
		return ;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
	{
		write(0, buf, 3);
		gbl->spc->s++;
	}
}
