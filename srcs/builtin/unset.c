/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:23:47 by pramella          #+#    #+#             */
/*   Updated: 2020/03/05 15:36:59 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_env(t_env **env, t_env *curr, t_env *prev)
{
    if (curr == *env)
        *env = curr->next;
    else if (!curr->next)
        prev->next = NULL;
    else
        prev->next = curr->next;
    free(curr->key);
    free(curr->value);
    free(curr);
}

int         builtin_unset(t_env **env, t_list *tkn)
{
    t_env   *prev;
    t_env   *curr;
    size_t  len;

    if (!env || !*env)
        return (-1);
    while (tkn)
    {
        len = ft_strlen(tkn->content);
        curr = *env;
        prev = *env;
        while (curr)
        {
            if (ft_strlen(curr->key) == len &&
                !ft_strncmp(curr->key, tkn->content, len))
            {
                remove_env(env, curr, prev);
                break ;
            }
            prev = curr;
            curr = curr->next;
        }
        tkn = tkn->next;
    }
    return (0);
}
