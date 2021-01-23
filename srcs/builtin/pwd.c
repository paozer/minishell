/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 22:12:28 by pramella          #+#    #+#             */
/*   Updated: 2020/03/07 17:45:59 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     builtin_pwd(void)
{
    char *buf;

    buf = getcwd(NULL, 0);
    if (!buf)
    {
        ft_fprintf(2, "minishell: pwd: %s\n", strerror(errno));
        return (1);
    }
    ft_printf("%s\n", buf);
    free(buf);
    return (0);
}
