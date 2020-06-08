/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:42:37 by pminne            #+#    #+#             */
/*   Updated: 2020/06/05 23:11:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		swap_temp(t_all *gbl, char **line, char *temp)
{
	move_cursor_left(&gbl->spc->s, gbl->term_key->left);
	ft_putstr_fd(gbl->term_key->clear, 0);
	*line ? free(*line) : 0;
	*line = ft_strdup(temp);
	free(temp);
	write(1, *line, ft_strlen(*line));
	gbl->spc->s = ft_strlen(*line);
}

int				check_file_history(void)
{
	int		fd;
	int		ret;

	ret = 0;
	fd = open(cp_gbl(PULL)->hst_path, O_RDONLY);
	ret = read(fd, NULL, 0);
	close(fd);
	if (ret != 0)
		return (0);
	return (1);
}

void			check_key_down(t_all *gbl, char *buf, char **line)
{
	char	*temp;
	t_dlst	*t_lst;

	temp = NULL;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
	{
		if (check_file_history() == 0)
			return ;
		if (!gbl->hst->data)
			return ;
		if (gbl->act_hst && !gbl->act_hst->next)
			temp = ft_strdup("");
		else if (gbl->act_hst && gbl->act_hst->next)
		{
			t_lst = gbl->act_hst->next;
			temp = ft_strdup(t_lst->data);
			gbl->act_hst = gbl->act_hst->next;
		}
		else if (!gbl->act_hst)
		{
			gbl->act_hst = gbl->hst->next;
			temp = ft_strdup(gbl->hst->data);
		}
		swap_temp(gbl, line, temp);
	}
}
