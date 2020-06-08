/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:25:14 by pramella          #+#    #+#             */
/*   Updated: 2020/05/07 00:53:04 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../minishell.h"

static t_list_fd	*ft_list_setup(int fd, t_list_fd **head)
{
	t_list_fd *node;
	t_list_fd *prev;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		prev = node;
		node = node->next;
	}
	if (!(node = malloc(sizeof(*node))) ||
		!(node->buf = malloc(BUFFER_SIZE + 1)))
	{
		free(node);
		return (NULL);
	}
	node->fd = fd;
	node->buf[0] = '\0';
	node->next = NULL;
	if (*head && prev)
		prev->next = node;
	else if (!*head)
		*head = node;
	return (node);
}

static int			ft_line_setup(t_list_fd *node, char **line)
{
	while (!(ft_strchr(node->buf, '\n')))
	{
		if (!node->buf[0])
			if ((node->ret = read(node->fd, node->buf, BUFFER_SIZE)) == -1)
				return (-1);
		node->buf[node->ret] = '\0';
		if (ft_strchr(node->buf, '\n'))
			break ;
		if (!(*line = ft_strjoin_gnl(*line, node->buf)))
			return (-1);
		node->buf[0] = '\0';
		if (node->ret == 0)
			return (1);
	}
	if (!(*line = ft_strjoin_gnl(*line, node->buf)))
		return (-1);
	node->buf = ft_cleanbuf_gnl(node->buf);
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_list_fd	*head;
	t_list_fd			*node;

	if (read(fd, NULL, 0) != 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (*line)
		*line = NULL;
	if (!(node = ft_list_setup(fd, &head)))
		return (-1);
	if (ft_line_setup(node, line) == -1)
		return (-1);
	if (cp_gbl(PULL)->hst_on == 0)
		node->ret = 0;
	if (node->ret == 0)
	{
		ft_lstclear_gnl(fd, &head);
		return (0);
	}
	return (1);
}
