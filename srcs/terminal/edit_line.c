/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:46:52 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:24:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_letter(char **line, char c, size_t h)
{
    size_t  i;
    size_t  j;
    char    *dst;
    char    *src;

    src = *line;
    if (!(dst = malloc(sizeof(*dst) * (ft_strlen(src) + 2))))
        return ;
    i = 0;
    j = 0;
    while (src[j])
    {
        if (i != h)
            dst[i++] = src[j++];
        else
            dst[i++] = c;
    }
    dst[i] = '\0';
    free(src);
    *line = dst;
}

char    *add_print(char *buf, t_shell *sh, char **line, int *padding_letter)
{
    if (sh->spc->s == ft_strlen(*line))
    {
        write(1, buf, 1);
        sh->spc->s++;
        return (buf);
    }
    ft_putstr_fd(sh->term_key->save, 0);
    ft_putstr_fd(sh->term_key->clear, 0);
    add_letter(line, buf[0], sh->spc->s);
    display_right(sh->spc->s, line);
    ft_putstr_fd(sh->term_key->reset, 0);
    ft_putstr_fd(buf, 1);
    *padding_letter += 1;
    sh->spc->s++;
    return (dup_key(buf));
}
