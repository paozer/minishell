/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:55:20 by pramella          #+#    #+#             */
/*   Updated: 2020/06/16 02:27:35 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!(node = malloc(sizeof(*node))) ||\
		!(node->buf = malloc(BUFFER_TRM + 1)))
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

char				*trm_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*sub;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_calloc(1, 1));
	if (len_s < len)
		len = len_s - start;
	if (!(sub = malloc(sizeof(*sub) * (len + 1))))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

static int			ft_line_setup(t_list_fd *node, char **line, t_shell *sh)
{
	while (!(ft_strchr(node->buf, '\n')))
	{
		if (node->buf[0] == '\0')
			if ((node->ret = read(node->fd, node->buf, BUFFER_TRM)) == -1)
				return (-1);
		node->buf[node->ret] = '\0';
		node->buf = check_move(node->buf, sh, line);
		if (ft_strchr(node->buf, '\n'))
			break ;
		if (!(*line = trm_strjoin_gnl(*line, node->buf)))
			return (-1);
		node->buf[0] = '\0';
		if (node->ret == 0)
			return (1);
	}
	if (!(*line = trm_strjoin_gnl(*line, node->buf)))
		return (-1);
	node->buf = trm_cleanbuf_gnl(node->buf);
	return (1);
}

int					trm_get_next_line(int fd, char **line, t_shell *sh)
{
	static t_list_fd	*head;
	t_list_fd			*node;

	if (read(fd, NULL, 0) != 0 || BUFFER_TRM <= 0)
		return (-1);
	if (*line)
		*line = NULL;
	if (!(node = ft_list_setup(fd, &head)))
		return (-1);
	get_shell(PULL)->s_head = head;
	if (ft_line_setup(node, line, sh) == -1)
		return (-1);
	if (node->ret == 0)
	{
		trm_lstclear_gnl(fd, &head);
		return (0);
	}
	return (1);
}
