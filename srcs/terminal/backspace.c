/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 04:10:36 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:24:46 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void loop_cut_characters(int s, char *dst, char *tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tmp[i])
    {
        if (i != s)
        {
            dst[j] = tmp[i];
            ++j;
        }
        ++i;
    }
    dst[j] = '\0';
}

static int  cut_characters(t_shell *sh, char **line)
{
    char *dst;
    char *tmp;

    tmp = *line;
    if (!(dst = malloc(sizeof(*dst) * ft_strlen(tmp))))
        return (0);
    loop_cut_characters(sh->spc->s - 1, dst, tmp);
    free(tmp);
    *line = dst;
    return (1);
}

char        *trm_backspace(t_shell *sh, char **line, char *buf)
{
    ft_putstr_fd(sh->term_key->left, 0);
    ft_putstr_fd(sh->term_key->save, 0);
    ft_putstr_fd(sh->term_key->clear, 0);
    if (cut_characters(sh, line) == 0)
    {
        write(2, "minishell: malloc: Error\n", 25);
        exit(EXIT_FAILURE);
    }
    display_right(sh->spc->s - 1, line);
    ft_putstr_fd(sh->term_key->reset, 0);
    sh->spc->s--;
    return (dup_key(buf));
}
