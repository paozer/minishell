/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:26:19 by pramella          #+#    #+#             */
/*   Updated: 2020/05/07 00:24:17 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;

	while (cmd)
	{
		ft_lstclear(&cmd->token, &free);
		ft_lstclear(&cmd->file_in, &free);
		ft_lstclear(&cmd->file_out, &free);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		free(env->key);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_term(t_trmkey *term_key, t_cnt *spc)
{
	free(term_key);
	free(spc->save);
	free(spc);
}

void	free_all(t_all *gbl)
{
	free_cmd(gbl->cmd);
	free_env(gbl->env);
	free_term(gbl->term_key, gbl->spc);
}
