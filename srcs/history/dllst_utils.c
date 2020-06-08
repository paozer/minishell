/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:44:59 by pramella          #+#    #+#             */
/*   Updated: 2020/06/08 19:05:16 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlst	*ft_dlstadd_back(t_dlst **hst, void *ctn)
{
	t_dlst	*act;
	t_dlst	*new;

	if (!hst)
		return (NULL);
	else if (!*hst && ctn)
		return (ft_newdlst(ctn));
	act = *hst;
	while (act->next)
		act = act->next;
	new = ft_newdlst(ctn);
	new->prev = act;
	act->next = new;
	return (new);
}

void	ft_dlstiter_up(t_dlst *hst)
{
	if (!hst->prev)
		ft_printf("%s\n", (char*)hst->data);
	else
	{
		while (hst->prev)
		{
			ft_printf("%s\n", (char*)hst->data);
			hst = hst->prev;
		}
		ft_printf("%s\n", (char*)hst->data);
	}
}

void	ft_dlstiter(t_dlst *hst)
{
	if (!hst->next)
		ft_printf("'%s'\n", (char*)hst->data);
	else
	{
		while (hst->next)
		{
			ft_printf("'%s'\n", (char*)hst->data);
			hst = hst->next;
		}
	}
}

void	ft_dlstclear(t_dlst **fst)
{
	t_dlst	*scd;
	t_dlst	*tmp;

	scd = *fst;
	while (scd)
	{
		tmp = scd->next;
		free(scd->data);
		free(scd);
		scd = tmp;
	}
	*fst = NULL;
}

t_dlst	*ft_newdlst(void *ctn)
{
	t_dlst	*dst;

	if (!(dst = malloc(sizeof(t_dlst))))
		return (NULL);
	if (ctn)
		dst->data = (void*)ft_strdup((char*)ctn);
	else
		dst->data = NULL;
	dst->prev = NULL;
	dst->next = NULL;
	return (dst);
}

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
