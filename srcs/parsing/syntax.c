/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:37:01 by pramella          #+#    #+#             */
/*   Updated: 2020/02/28 19:08:39 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  print_error(void)
{
    write(2, "\nminishell: syntax error near unexpected token\n", 47);
    return (0);
}

static int  valid_pipes(char *str)
{
    size_t  i;
    size_t  curr;

    if (is_first_char(str, "|") || is_last_char(str, "|"))
        return (print_error());
    curr = 0;
    while (curr == 0 || str[curr])
    {
        (curr == 0) ? (curr = get_non_escaped(str, curr, "|")) : 0;
        if (!str[curr])
            break ;
        i = curr + 1;
        while (ft_isspace(str[i]))
            ++i;
        if (ft_isinset(str[i], "|;"))
            return (print_error());
        curr = get_non_escaped(str, curr + 1, "|");
    }
    return (1);
}

static int  valid_redirect(char *str)
{
    size_t  i;
    size_t  curr;

    if (is_last_char(str, "<>"))
        return (print_error());
    curr = 0;
    while (curr == 0 || str[curr])
    {
        (curr == 0) ? (curr = get_non_escaped(str, curr, "<>")) : 0;
        if (!str[curr])
            break ;
        i = curr + 1;
        if ((ft_isinset(str[i], "<>") && str[i] != str[curr]) || !str[i])
            return (print_error());
        (str[i] == str[curr]) ? ++i : 0;
        while (ft_isspace(str[i]))
            ++i;
        if (ft_isinset(str[i], "<>;|"))
            return (print_error());
        curr = get_non_escaped(str, curr + 1, "<>");
    }
    return (1);
}

static int  valid_semicolon(char *str)
{
    size_t  i;
    size_t  curr;

    if (is_first_char(str, ";"))
        return (print_error());
    curr = 0;
    while (curr == 0 || str[curr])
    {
        (curr == 0) ? (curr = get_non_escaped(str, curr, ";")) : 0;
        if (!str[curr])
            break ;
        i = curr + 1;
        while (ft_isspace(str[i]))
            ++i;
        if (ft_isinset(str[i], ";|"))
            return (print_error());
        curr = get_non_escaped(str, curr + 1, ";");
    }
    return (1);
}

/*
** checks line for syntax errors related to pipe, redirect and semicolon chars
**
** @arg: line read from terminal before parsing
** @ret: true = syntax ok false = syntax error
*/

int         valid_syntax(char *line)
{
    if (!line[0])
        return (1);
    if (!valid_pipes(line) || !valid_redirect(line) || !valid_semicolon(line))
        return (0);
    return (1);
}
