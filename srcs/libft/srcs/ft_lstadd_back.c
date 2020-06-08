/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:25:23 by pramella          #+#    #+#             */
/*   Updated: 2020/03/02 21:25:28 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		new->next = NULL;
		return ;
	}
	last = ft_lstlast(*alst);
	last->next = new;
	new->next = NULL;
}
