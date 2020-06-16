/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:52:08 by pramella          #+#    #+#             */
/*   Updated: 2020/06/16 02:25:24 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** exit [n] exits with status n when n is ommited the last exit status is used
** if > one arg and first non num: num arg required > exit
** if > one arg and first num: too many args > no exit
** if one arg always exit: if non num > numeric argument required
*/

static int	is_valid_option(t_shell *sh, t_list *tkn)
{
	size_t	i;
	char	c;

	i = 0;
	while (((char *)tkn->content)[i])
	{
		c = ((char *)tkn->content)[i];
		if (!ft_isdigit(c) && !ft_isspace(c) && c != 43 && c != 45)
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
					tkn->content);
			sh->last_exit = 2;
			return (1);
		}
		++i;
	}
	if (tkn->next)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		sh->last_exit = 1;
		return (0);
	}
	sh->last_exit = (unsigned int)ft_atoi(tkn->content);
	return (1);
}

void		builtin_exit(t_shell *sh, t_list *tkn)
{
	int exit_value;

	write(2, "exit\n", 5);
	if (tkn && !is_valid_option(sh, tkn))
		return ;
	free_all(sh);
	if (sh->hst && sh->hst->data)
	{
		dllst_save(sh->hst_path, sh->hst);
		dllst_clear(&sh->hst);
	}
	else if (sh->hst)
		free(sh->hst);
	trm_lstclear_gnl(0, &sh->s_head);
	free(sh->hst_path);
	tcsetattr(0, 0, &(sh->old_term));
	exit_value = sh->last_exit;
	free(sh);
	exit(exit_value);
}
