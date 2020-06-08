/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:13 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:21:14 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *head;
	t_list *node;
	t_list *last;

	if (!lst || !(*f))
		return (NULL);
	if (!(head = ft_lstnew((*f)(lst->content))))
		return (NULL);
	lst = lst->next;
	last = head;
	while (lst)
	{
		if (!(node = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&head, (*del));
			return (NULL);
		}
		last->next = node;
		last = node;
		lst = lst->next;
	}
	return (head);
}
