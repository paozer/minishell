/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:45:18 by pramella          #+#    #+#             */
/*   Updated: 2020/05/06 15:30:49 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlst	*pull_history(int fd, t_all *gbl)
{
	char	*line;
	t_dlst	*act_hst;

	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		!(gbl->hst->data) ? (gbl->hst->data = (void*)ft_strdup(line)) :
			(act_hst = ft_dlstadd_back(&gbl->hst, (void*)line));
		free(line);
	}
	!(gbl->hst->data) ? (gbl->hst->data = (void*)ft_strdup(line)) :
		(act_hst = ft_dlstadd_back(&gbl->hst, (void*)line));
	free(line);
	close(fd);
	return (act_hst);
}

t_dlst	*check_history(t_all *gbl)
{
	int		fd;

	fd = open(gbl->hst_path, O_RDONLY);
	gbl->hst = ft_newdlst(NULL);
	if (fd < 0)
	{
		fd = open(gbl->hst_path, O_CREAT | O_RDWR, 0644);
		close(fd);
		return (NULL);
	}
	return (pull_history(fd, gbl));
}
