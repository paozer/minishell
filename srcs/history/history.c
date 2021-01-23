/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:45:18 by pramella          #+#    #+#             */
/*   Updated: 2020/06/16 02:25:24 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlst  *pull_history(int fd, t_shell *sh)
{
    char    *line;
    t_dlst  *act_hst;

    line = NULL;
    while (get_next_line(fd, &line))
    {
        (!sh->hst->data) ? (sh->hst->data = ft_strdup(line)) :
            (act_hst = dllst_add_back(&sh->hst, line));
        free(line);
    }
    (!sh->hst->data) ? (sh->hst->data = ft_strdup(line)) :
        (act_hst = dllst_add_back(&sh->hst, line));
    free(line);
    close(fd);
    return (act_hst);
}

t_dlst  *check_history(t_shell *sh)
{
    int fd;

    sh->hst = dllst_new(NULL);
    if ((fd = open(sh->hst_path, O_RDONLY)) < 0)
    {
        fd = open(sh->hst_path, O_CREAT | O_RDWR, 0644);
        close(fd);
        return (NULL);
    }
    return (pull_history(fd, sh));
}
