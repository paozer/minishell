/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:52:20 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 21:39:50 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		F1 => COPY ON
**		F2 => COPY DONE
**		F3 => PASTE
*/

#include "../minishell.h"

char	*ft_realloc_str(char *src, char c)
{
	char	*dst;
	int		i;

	i = 0;
	if (!src)
	{
		if (!(dst = malloc(2)))
			return (NULL);
		dst[0] = c;
		dst[1] = '\0';
		return (dst);
	}
	if (!(dst = malloc(sizeof(*dst) * (ft_strlen(src) + 2))))
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i++] = c;
	dst[i] = '\0';
	free(src);
	return (dst);
}

void	copy_on(t_all *gbl, char *buf, char **line)
{
	char *temp;

	temp = NULL;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67
			&& ft_strlen(*line) > gbl->spc->s)
	{
		temp = ft_strdup(*line);
		ft_putstr_fd(buf, 0);
		gbl->spc->s++;
		gbl->spc->save = ft_realloc_str(gbl->spc->save, temp[gbl->spc->s]);
		free(temp);
	}
}

int		check_copy(t_all *gbl, char *buf, char **line)
{
	static int	on = 0;
	char		*temp;

	if (!*line)
		return (0);
	if (buf[0] == 27 && buf[1] == 79 && buf[2] == 80 && on == 0)
	{
		temp = ft_strdup(*line);
		gbl->spc->save = ft_realloc_str(gbl->spc->save, temp[gbl->spc->s]);
		free(temp);
		on = 1;
	}
	if (buf[0] == 27 && buf[1] == 79 && buf[2] == 81 && on == 1)
		on = 0;
	if (on == 1)
		copy_on(gbl, buf, line);
	return (on);
}

void	loop_add_word(char *dst, char *src, char *str, int h)
{
	t_normcpy	cnt;

	cnt.i = 0;
	cnt.w = 0;
	cnt.a = 0;
	while (src[cnt.w])
	{
		if (cnt.i == h)
		{
			while (str[cnt.a])
			{
				dst[cnt.i] = str[cnt.a];
				cnt.i++;
				cnt.a++;
			}
		}
		else
		{
			dst[cnt.i] = src[cnt.w];
			cnt.i++;
			cnt.w++;
		}
	}
	dst[cnt.i] = '\0';
}

void	add_word(char **line, char *str, int h)
{
	char	*dst;
	char	*src;

	src = *line;
	if (h == (int)ft_strlen(*line))
	{
		dst = ft_strjoin(*line, str);
		(src) ? (free(src)) : 0;
		*line = dst;
		return ;
	}
	if (!(dst = malloc(ft_strlen(src) + ft_strlen(str) + 1)))
		return ;
	loop_add_word(dst, src, str, h);
	(src) ? (free(src)) : 0;
	*line = dst;
}
