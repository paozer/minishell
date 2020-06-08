/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:25:22 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:25:23 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		++i;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	if (!(str = malloc(sizeof(*str) * len)))
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	free((char *)s1);
	s1 = NULL;
	while (s2 && s2[j] && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_cleanbuf_gnl(char *str)
{
	size_t i;
	size_t start;

	i = 0;
	start = ft_strlen_gnl(str) + 1;
	while (str[start + i])
	{
		str[i] = str[start + i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

void	ft_lstclear_gnl(int fd, t_list_fd **head)
{
	t_list_fd *node;
	t_list_fd *prev;

	node = *head;
	prev = NULL;
	while (node)
	{
		if (node->fd == fd)
			break ;
		prev = node;
		node = node->next;
	}
	if (prev)
		prev->next = node->next;
	else
		*head = NULL;
	free(node->buf);
	node->buf = NULL;
	free(node);
	node = NULL;
}
