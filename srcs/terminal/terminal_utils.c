/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 22:17:05 by pminne            #+#    #+#             */
/*   Updated: 2020/05/07 01:01:25 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*terminal_hub(t_all *gbl, char *buf, char **line)
{
	check_key_right(gbl, buf, line);
	check_key_left(gbl, buf);
	check_key_up(gbl, buf, line);
	check_key_down(gbl, buf, line);
	check_paste(gbl, buf, line);
	check_home(gbl, buf);
	check_end(gbl, buf, line);
	return (dup_key(buf));
}

void		handle_ctrl_d(t_all *gbl, char **line)
{
	if (*line)
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
		ft_printf("%c", buf[0]);
		gbl->spc->s++;
	}
	if (buf[0] == 10)
	{
		if (*line && ft_strlen(*line) == 0)
			return (empty_new_line(line, buf));
		if (*line && is_only_whitespace(*line) == 0)
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
	char	*clear;

	clear = ft_strdup("clear");
	if (*line)
		free(*line);
	*line = clear;
	buf[0] = '\n';
	ft_putstr_fd("\n", 1);
	return (buf);
}

char		*check_move(char *buf, t_all *gbl, char **line)
{
	static int	padding_letter = 0;

	if (buf[0] == 4 && !*line)
		handle_ctrl_d(gbl, line);
	if (buf[0] == 9)
		return (dup_key(buf));
	else if (buf[0] == 4 && ft_strncmp(*line, "", 1) == 0)
		handle_ctrl_d(gbl, line);
	if (check_copy(gbl, buf, line) == 1)
		return (dup_key(buf));
	if (buf[0] == 12)
		return (clear_term(line, buf));
	if (buf[0] == 127 && gbl->spc->s == 0)
		return (dup_key(buf));
	else if (buf[0] == 127 && *line && gbl->spc->s > 0)
		return (trm_backspace(gbl, line, buf));
	return (check_move_next(buf, gbl, line, &padding_letter));
}
