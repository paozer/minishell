/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 04:46:08 by pminne            #+#    #+#             */
/*   Updated: 2020/05/04 04:46:24 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_paste(t_all *gbl, char *buf, char **line)
{
	int i;

	if (!gbl->spc->save)
		return ;
	if (buf[0] == 27 && buf[1] == 79 && buf[2] == 82)
	{
		i = 0;
		ft_putstr_fd(gbl->term_key->save, 0);
		ft_putstr_fd(gbl->term_key->clear, 0);
		add_word(line, gbl->spc->save, gbl->spc->s);
		while (gbl->spc->save[i])
		{
			ft_printf("%c", gbl->spc->save[i]);
			i++;
		}
		gbl->spc->s += i;
		ft_putstr_fd(gbl->term_key->save, 0);
		display_right(gbl->spc->s, line);
		ft_putstr_fd(gbl->term_key->reset, 0);
		free(gbl->spc->save);
	}
}
