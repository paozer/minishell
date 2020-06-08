/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:42:26 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 19:06:35 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*security_history_up(t_all *gbl)
{
	char	*temp;

	temp = NULL;
	if (check_file_history() == 0)
		return (NULL);
	if (!gbl->hst->data)
		return (NULL);
	if (!gbl->act_hst)
	{
		temp = ft_strdup(gbl->hst->data);
		gbl->act_hst = gbl->hst;
	}
	else if (gbl->act_hst)
	{
		temp = ft_strdup(gbl->act_hst->data);
		gbl->act_hst = gbl->act_hst->prev;
	}
	return (temp);
}

void	check_key_up(t_all *gbl, char *buf, char **line)
{
	char	*temp;

	temp = NULL;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
	{
		temp = security_history_up(gbl);
		if (!temp)
			return ;
		move_cursor_left(&gbl->spc->s, gbl->term_key->left);
		ft_putstr_fd(gbl->term_key->clear, 0);
		*line ? free(*line) : 0;
		*line = ft_strdup(temp);
		free(temp);
		write(1, *line, ft_strlen(*line));
		gbl->spc->s = ft_strlen(*line);
	}
}
