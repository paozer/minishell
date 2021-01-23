/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:42:37 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:27:35 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         check_file_history(void)
{
    int     fd;
    int     ret;

    fd = open(get_shell(PULL)->hst_path, O_RDONLY);
    ret = 0;
    ret = read(fd, NULL, 0);
    close(fd);
    if (ret != 0)
        return (0);
    return (1);
}

static void swap_temp(t_shell *sh, char **line, char *temp)
{
    move_cursor_left(&sh->spc->s, sh->term_key->left);
    ft_putstr_fd(sh->term_key->clear, 0);
    free(*line);
    *line = ft_strdup(temp);
    free(temp);
    write(1, *line, ft_strlen(*line));
    sh->spc->s = ft_strlen(*line);
}

void        check_key_down(t_shell *sh, char *buf, char **line)
{
    char    *temp;
    t_dlst  *t_lst;

    temp = NULL;
    if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
    {
        if (check_file_history() == 0 || !sh->hst->data)
            return ;
        if (sh->act_hst && !sh->act_hst->next)
            temp = ft_strdup("");
        else if (sh->act_hst && sh->act_hst->next)
        {
            t_lst = sh->act_hst->next;
            temp = ft_strdup(t_lst->data);
            sh->act_hst = sh->act_hst->next;
        }
        else if (!sh->act_hst)
        {
            sh->act_hst = sh->hst->next;
            temp = ft_strdup(sh->hst->data);
        }
        swap_temp(sh, line, temp);
    }
}

char        *security_history_up(t_shell *sh)
{
    char *temp;

    if (check_file_history() == 0 || !sh->hst->data)
        return (NULL);
    temp = NULL;
    if (!sh->act_hst)
    {
        temp = ft_strdup(sh->hst->data);
        sh->act_hst = sh->hst;
    }
    else if (sh->act_hst)
    {
        temp = ft_strdup(sh->act_hst->data);
        sh->act_hst = sh->act_hst->prev;
    }
    return (temp);
}

void        check_key_up(t_shell *sh, char *buf, char **line)
{
    char    *temp;

    temp = NULL;
    if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
    {
        temp = security_history_up(sh);
        if (!temp)
            return ;
        move_cursor_left(&sh->spc->s, sh->term_key->left);
        ft_putstr_fd(sh->term_key->clear, 0);
        free(*line);
        *line = ft_strdup(temp);
        free(temp);
        write(1, *line, ft_strlen(*line));
        sh->spc->s = ft_strlen(*line);
    }
}
