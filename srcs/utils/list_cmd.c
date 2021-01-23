/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:25:09 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:25:11 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Utilities used to handle the list of cmds
*/

void    cmd_add_back(t_cmd **begin, char *id)
{
    t_cmd *new;
    t_cmd *curr;

    new = cmd_new();
    if (!begin || !new)
    {
        free(new);
        return ;
    }
    tkn_add_back(&new, id);
    if (!*begin)
    {
        *begin = new;
        return ;
    }
    curr = cmd_last(begin);
    curr->next = new;
}

t_cmd   *cmd_new(void)
{
    t_cmd *new;

    if (!(new = malloc(sizeof(*new))))
    {
        ft_fprintf(2, "minishell: malloc: %s\n", strerror(errno));
        return (NULL);
    }
    new->token = NULL;
    new->file_in = NULL;
    new->file_out = NULL;
    new->std_in = STDIN_FILENO;
    new->std_out = STDOUT_FILENO;
    new->fd_copy_in = STDIN_FILENO;
    new->fd_copy_out = STDOUT_FILENO;
    new->p_in[0] = -1;
    new->p_in[1] = -1;
    new->p_out[0] = -1;
    new->p_out[1] = -1;
    new->append = 0;
    new->next = NULL;
    return (new);
}

t_cmd   *cmd_last(t_cmd **begin)
{
    t_cmd *curr;

    if (!begin || !*begin)
        return (NULL);
    curr = *begin;
    while (curr->next)
        curr = curr->next;
    return (curr);
}
