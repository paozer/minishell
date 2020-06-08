/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_gnl_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:14:07 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 21:25:24 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	trm_strlen_gnl(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		++i;
	return (i);
}

/*
** if s1 contains \n > massive fuckup
** trm_strlen_gnl(s1) will be to small and first while
** will copy to much of s1 into str
*/

char	*trm_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	len = trm_strlen_gnl(s1) + trm_strlen_gnl(s2) + 1;
	if (!(str = malloc(sizeof(*str) * len)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	free((char *)s1);
	s1 = NULL;
	while (s2[j] && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}

char	*trm_cleanbuf_gnl(char *str)
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

void	trm_lstclear_gnl(int fd, t_list_fd **head)
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
	if (prev != NULL)
		prev->next = node->next;
	else
		*head = NULL;
	free(node->buf);
	node->buf = NULL;
	free(node);
	node = NULL;
}
