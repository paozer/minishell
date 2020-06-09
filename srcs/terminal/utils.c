/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 22:17:05 by pminne            #+#    #+#             */
/*   Updated: 2020/06/09 13:19:54 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*terminal_hub(t_all *gbl, char *buf, char **line)
{
	check_key_right(gbl, buf, line);
	check_key_left(gbl, buf);
	check_key_up(gbl, buf, line);
	check_key_down(gbl, buf, line);
	check_home(gbl, buf);
	check_end(gbl, buf, line);
	return (dup_key(buf));
}

void		handle_ctrl_d(t_all *gbl, char **line)
{
	free(*line);
	builtin_exit(gbl, NULL);
}

char		*check_move_next(char *buf, t_all *gbl,
					char **line, int *padding_letter)
{
	if (buf[0] == 4)
	{
		buf[0] = -1;
		return (dup_key(buf));
	}
	if (ft_strlen(buf) == 1 && !*line && buf[0] != 127)
	{
		write(1, buf, 1);
		gbl->spc->s++;
	}
	if (buf[0] == 10)
	{
		if (*line && (ft_strlen(*line) == 0 || is_only_whitespace(*line)))
			return (empty_new_line(line, buf));
		*padding_letter = 0;
		return (buf);
	}
	else if (ft_strlen(buf) == 1 && *line)
		return (add_print(buf, gbl, line, padding_letter));
	*padding_letter = 0;
	if (ft_strlen(buf) == 3)
		return (terminal_hub(gbl, buf, line));
	return (buf);
}

static char	*clear_term(char **line, char *buf)
{
	char *clear;

	clear = ft_strdup("clear");
	free(*line);
	*line = clear;
	buf[0] = '\n';
	write(1, "\n", 1);
	return (buf);
}

char		*check_move(char *buf, t_all *gbl, char **line)
{
	static int	padding_letter = 0;

	if (buf[0] == 4 && (!*line || ft_strncmp(*line, "", 1) == 0))
		handle_ctrl_d(gbl, line);
	else if (buf[0] == 9)
		return (dup_key(buf));
	else if (buf[0] == 12)
		return (clear_term(line, buf));
	else if (buf[0] == 127)
	{
		if (gbl->spc->s == 0)
			return (dup_key(buf));
		if (*line && gbl->spc->s > 0)
			return (trm_backspace(gbl, line, buf));
	}
	return (check_move_next(buf, gbl, line, &padding_letter));
}
