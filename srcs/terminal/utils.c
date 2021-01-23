/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 22:17:05 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:24:46 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        *terminal_hub(t_shell *sh, char *buf, char **line)
{
    check_key_right(sh, buf, line);
    check_key_left(sh, buf);
    check_key_up(sh, buf, line);
    check_key_down(sh, buf, line);
    check_home(sh, buf);
    check_end(sh, buf, line);
    return (dup_key(buf));
}

void        handle_ctrl_d(t_shell *sh, char **line)
{
    free(*line);
    builtin_exit(sh, NULL);
}

char        *check_move_next(char *buf, t_shell *sh,
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
        sh->spc->s++;
    }
    if (buf[0] == 10)
    {
        if (*line && (ft_strlen(*line) == 0 || is_only_whitespace(*line)))
            return (empty_new_line(line, buf));
        *padding_letter = 0;
        return (buf);
    }
    else if (ft_strlen(buf) == 1 && *line)
        return (add_print(buf, sh, line, padding_letter));
    *padding_letter = 0;
    if (ft_strlen(buf) == 3)
        return (terminal_hub(sh, buf, line));
    return (buf);
}

static char *clear_term(char **line, char *buf)
{
    free(*line);
    *line = ft_strdup("clear");
    buf[0] = '\n';
    write(1, "\n", 1);
    return (buf);
}

char        *check_move(char *buf, t_shell *sh, char **line)
{
    static int padding_letter = 0;

    if (buf[0] == 4 && (!*line || ft_strncmp(*line, "", 1) == 0))
        handle_ctrl_d(sh, line);
    else if (buf[0] == 9)
        return (dup_key(buf));
    else if (buf[0] == 12)
        return (clear_term(line, buf));
    else if (buf[0] == 127)
    {
        if (sh->spc->s == 0)
            return (dup_key(buf));
        if (*line && sh->spc->s > 0)
            return (trm_backspace(sh, line, buf));
    }
    return (check_move_next(buf, sh, line, &padding_letter));
}
