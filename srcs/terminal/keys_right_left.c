/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_right_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:45:08 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:24:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_key_left(t_shell *sh, char *buf)
{
	if (sh->spc->s == 0)
		return ;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
	{
		ft_putstr_fd(buf, 0);
		sh->spc->s--;
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

void	check_key_right(t_shell *sh, char *buf, char **line)
{
	if (!*line || sh->spc->s == ft_strlen(*line))
		return ;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
	{
		write(0, buf, 3);
		sh->spc->s++;
	}
}
