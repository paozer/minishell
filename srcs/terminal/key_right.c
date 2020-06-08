/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:45:08 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 19:20:06 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_right(int i, char **line)
{
	char *s;

	s = *line;
	while (s[i])
	{
		ft_printf("%c", s[i]);
		i++;
	}
}

void	check_key_right(t_all *gbl, char *buf, char **line)
{
	if (!*line)
		return ;
	if (gbl->spc->s == (unsigned int)ft_strlen(*line))
		return ;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
	{
		ft_putstr_fd(buf, 0);
		gbl->spc->s++;
	}
}
