/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:43:44 by pramella          #+#    #+#             */
/*   Updated: 2020/03/06 15:43:14 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void builtin_export_no_args(t_env *env)
{
    while (env)
    {
        if (env->set)
            ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
        env = env->next;
    }
}

static void handle_logic(t_env *env, t_list *tkn)
{
    size_t  i;
    t_env   *tmp;

    if (!is_var_declaration(tkn->content))
    {
        ft_fprintf(2, "minishell: export: %s : not a valid identifier\n",\
                tkn->content);
        return ;
    }
    i = find_char(tkn->content, '=');
    if (((char *)tkn->content)[i] == '=')
    {
        tmp = env_new(ft_substr(tkn->content, 0, i), ft_substr(
            tkn->content, i + 1, ft_strlen(tkn->content + i + 1)), 1);
        env_add_back(&env, tmp);
    }
}

int         builtin_export(t_env *env, t_list *tkn)
{
    t_env *tmp;

    (!tkn) ? builtin_export_no_args(env) : 0;
    while (tkn)
    {
        if ((tmp = get_env(env, tkn->content)))
        {
            if (is_var_declaration(tkn->content))
                set_env_value(tmp, tkn->content);
            tmp->set = 1;
        }
        else
            handle_logic(env, tkn);
        tkn = tkn->next;
    }
    return (0);
}
