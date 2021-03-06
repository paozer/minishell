/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 21:32:22 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:24:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *dup_key(char *buf)
{
    char *dst;

    if (!(dst = malloc(sizeof(*dst) * (BUFFER_SIZE + 1))))
        return (NULL);
    dst[0] = '\0';
    free(buf);
    return (dst);
}

void    move_cursor_left(unsigned int *s, char *left)
{
    while (*s)
    {
        ft_putstr_fd(left, 0);
        *s -= 1;
    }
}

void    check_home(t_shell *sh, char *buf)
{
    if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
    {
        move_cursor_left(&sh->spc->s, sh->term_key->left);
    }
}

void    check_end(t_shell *sh, char *buf, char **line)
{
    if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
    {
        while (sh->spc->s < ft_strlen(*line))
        {
            ft_putstr_fd(sh->term_key->right, 0);
            sh->spc->s += 1;
        }
    }
}

char    *empty_new_line(char **line, char *buf)
{
    write(1, "\n", 1);
    free(*line);
    *line = NULL;
    return (buf);
}
