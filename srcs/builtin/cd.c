/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:18:38 by pramella          #+#    #+#             */
/*   Updated: 2020/06/08 10:35:02 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *replace_tilde(t_env *env, char *path, int flag)
{
    char    *new;
    t_env   *tmp;

    if (!(tmp = get_env(env, "HOME")))
    {
        write(2, "minishell: cd: HOME not set\n", 28);
        (flag) ? free(path) : 0;
        return (NULL);
    }
    new = ft_strjoin(tmp->value, path + 1);
    (flag) ? free(path) : 0;
    return (new);
}

static int  cd_path(t_env *env, char *path, int flag)
{
    char    *pwd;
    t_env   *tmp;
    t_env   *tmp_old;

    if (path && path[0] == '~' && !(path = replace_tilde(env, path, flag)))
        return (1);
    if (chdir(path) == -1)
    {
        ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
        return (1);
    }
    if ((tmp = get_env(env, "PWD")) &&
        (tmp_old = get_env(env, "OLDPWD")))
        set_env_value(tmp_old, tmp->value);
    if (!(pwd = getcwd(NULL, 0)))
    {
        ft_fprintf(2, "minishell: getcwd: %s\n", strerror(errno));
        return (1);
    }
    if (tmp)
        set_env_value(tmp, pwd);
    free(pwd);
    return (0);
}

int         builtin_cd(t_env *env, t_list *tkn)
{
    if (!tkn)
        return (cd_path(env, ft_strdup("~"), 1));
    return (cd_path(env, tkn->content, 0));
}
