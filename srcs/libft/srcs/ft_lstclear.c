/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:20:48 by pramella          #+#    #+#             */
/*   Updated: 2020/03/03 16:20:49 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *current;
	t_list *trash;

	if (!lst || !*lst || !(*del))
		return ;
	current = *lst;
	while (current)
	{
		trash = current->next;
		ft_lstdelone(current, (*del));
		current = trash;
	}
	*lst = NULL;
}
