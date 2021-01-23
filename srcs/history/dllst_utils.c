/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:44:59 by pramella          #+#    #+#             */
/*   Updated: 2020/06/09 12:27:52 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlst  *dllst_add_back(t_dlst **hst, void *ctn)
{
    t_dlst  *act;
    t_dlst  *new;

    if (!hst)
        return (NULL);
    else if (!*hst && ctn)
        return (dllst_new(ctn));
    act = *hst;
    while (act->next)
        act = act->next;
    new = dllst_new(ctn);
    new->prev = act;
    act->next = new;
    return (new);
}

void    dllst_clear(t_dlst **fst)
{
    t_dlst  *scd;
    t_dlst  *tmp;

    scd = *fst;
    while (scd)
    {
        tmp = scd->next;
        free(scd->data);
        free(scd);
        scd = tmp;
    }
    *fst = NULL;
}

t_dlst  *dllst_new(void *ctn)
{
    t_dlst  *dst;

    if (!(dst = malloc(sizeof(*dst))))
        return (NULL);
    if (ctn)
        dst->data = ft_strdup(ctn);
    else
        dst->data = NULL;
    dst->prev = NULL;
    dst->next = NULL;
    return (dst);
}

int     dllst_save(char *filename, t_dlst *hst)
{
    int fd;
    int ret;
    size_t len;

    if (!hst || (fd = open(filename, O_CREAT | O_RDWR, 0644)) < 0)
        return (-1);
    while (hst)
    {
        len = ft_strlen(hst->data);
        if (len > 0 && (ret = write(fd, hst->data, len)) == 0)
            return (-1);
        (len > 0 ) ? write(fd, "\n", 1) : 0;
        hst = hst->next;
    }
    close(fd);
    return (0);
}
