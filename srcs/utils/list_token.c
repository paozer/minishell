/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:25:17 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:25:18 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Utilities used to handle the list of tokens
*/

void    tkn_add_back(t_cmd **begin, char *content)
{
    t_list  *new;
    t_cmd   *cmd;

    new = ft_lstnew(content);
    if (!begin || !new)
    {
        free(new);
        return ;
    }
    cmd = cmd_last(begin);
    ft_lstadd_back(&cmd->token, new);
}
