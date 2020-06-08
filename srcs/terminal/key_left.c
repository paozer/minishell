/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:45:38 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 18:52:09 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_key_left(t_all *gbl, char *buf)
{
	if (gbl->spc->s == 0)
		return ;
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
	{
		ft_putstr_fd(buf, 0);
		gbl->spc->s--;
	}
}
