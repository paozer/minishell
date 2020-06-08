/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:45:09 by pramella          #+#    #+#             */
/*   Updated: 2020/05/06 15:33:55 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_dlst_save(char *filename, t_dlst *hst)
{
	int fd;
	int ret;

	if (!hst)
		return (-1);
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	ret = 0;
	if (fd < 0)
		return (-1);
	while (hst->next)
	{
		if (ft_strlen((char*)hst->data) > 0)
		{
			ret = write(fd, hst->data, ft_strlen((char*)hst->data));
			if (ret == 0)
				return (-1);
			write(fd, "\n", 1);
		}
		hst = hst->next;
	}
	write(fd, hst->data, ft_strlen((char*)hst->data));
	close(fd);
	return (0);
}

void	ft_dlst_down(t_dlst **act)
{
	t_dlst *mv;

	mv = *act;
	if (!mv->next)
		return ;
	mv = mv->next;
	*act = mv;
}

void	ft_dlst_up(t_dlst **act)
{
	t_dlst *mv;

	mv = *act;
	if (mv->prev)
		return ;
	mv = mv->prev;
	*act = mv;
}
