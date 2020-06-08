/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:46:52 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 19:20:38 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_letter(char **line, char c, int h)
{
	int		i;
	int		w;
	char	*dst;
	char	*src;

	src = *line;
	if (!(dst = malloc(sizeof(char) * (ft_strlen(src) + 2))))
		return ;
	i = 0;
	w = 0;
	while (src[w])
	{
		if (i == h)
			dst[i++] = c;
		else
		{
			dst[i] = src[w];
			i++;
			w++;
		}
	}
	dst[i] = '\0';
	(src) ? free(src) : 0;
	*line = dst;
}

char	*add_print(char *buf, t_all *gbl, char **line, int *padding_letter)
{
	if (gbl->spc->s == (unsigned int)ft_strlen(*line))
	{
		ft_printf("%c", buf[0]);
		gbl->spc->s++;
		return (buf);
	}
	else
	{
		ft_putstr_fd(gbl->term_key->save, 0);
		ft_putstr_fd(gbl->term_key->clear, 0);
		add_letter(line, buf[0], gbl->spc->s);
		display_right(gbl->spc->s, line);
		ft_putstr_fd(gbl->term_key->reset, 0);
		ft_putstr_fd(buf, 1);
		*padding_letter += 1;
		gbl->spc->s++;
		return (dup_key(buf));
	}
}
