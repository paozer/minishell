/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:37:34 by pramella          #+#    #+#             */
/*   Updated: 2020/02/29 00:38:03 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** returns index of the next non escaped (by ', \ or ") sep char or \0
** starts searching from i
*/

size_t  get_non_escaped(char *str, size_t i, char *sep)
{
    int sq;
    int dq;

    sq = 0;
    dq = 0;
    while (str[i])
    {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
                && dq == 0 && sq == 0)
            ++dq;
        else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\') && dq == 1)
            --dq;
        if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
                && sq == 0 && dq == 0)
            ++sq;
        else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\') && sq == 1)
            --sq;
        if (ft_isinset(str[i], sep) && (i == 0 || str[i - 1] != '\\')
                && sq == 0 && dq == 0)
            return (i);
        ++i;
    }
    return (i);
}

/*
** returns index of the next non escaped (by ' or \) sep char or \0
** starts searching from i
*/

size_t  get_non_escaped2(char *str, size_t i, char *sep)
{
    int sq;
    int dq;

    sq = 0;
    dq = 0;
    while (str[i])
    {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
                && dq == 0 && sq == 0)
            ++dq;
        else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\') && dq == 1)
            --dq;
        if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
                && sq == 0 && dq == 0)
            ++sq;
        else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\') && sq == 1)
            --sq;
        if (ft_isinset(str[i], sep) && (i == 0 || str[i - 1] != '\\')
                && sq == 0)
            return (i);
        ++i;
    }
    return (i);
}

int     is_first_char(char *str, char *set)
{
    size_t i;

    i = 0;
    while (ft_isspace(str[i]))
        ++i;
    if (ft_isinset(str[i], set))
        return (1);
    return (0);
}

int     is_last_char(char *str, char *set)
{
    size_t i;

    i = ft_strlen(str) - 1;
    while (ft_isspace(str[i]))
        --i;
    if (ft_isinset(str[i], set) && (i == 0 || str[i - 1] != '\\'))
        return (1);
    return (0);
}

size_t  find_char(char *s, char c)
{
    size_t i;

    i = 0;
    while (s[i] && s[i] != c)
        ++i;
    return (i);
}
