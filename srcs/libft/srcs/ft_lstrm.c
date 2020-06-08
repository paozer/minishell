/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:24:37 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:24:37 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrm(t_list **begin, t_list *prev, t_list *curr)
{
	if (curr == *begin)
		*begin = curr->next;
	else if (!curr->next)
		prev->next = NULL;
	else
		prev->next = curr->next;
	free(curr->content);
	free(curr);
}
