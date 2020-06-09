/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:52:08 by pramella          #+#    #+#             */
/*   Updated: 2020/06/09 12:27:43 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** exit [n] exits with status n when n is ommited the last exit status is used
** if > one arg and first non num: num arg required > exit
** if > one arg and first num: too many args > no exit
** if one arg always exit: if non num > numeric argument required
*/

static int	is_valid_option(t_all *gbl, t_list *tkn)
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
			gbl->last_exit = 2;
			return (1);
		}
		++i;
	}
	if (tkn->next)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		gbl->last_exit = 1;
		return (0);
	}
	gbl->last_exit = (unsigned int)ft_atoi(tkn->content);
	return (1);
}

void		builtin_exit(t_all *gbl, t_list *tkn)
{
	int exit_value;

	write(2, "exit\n", 5);
	if (tkn && !is_valid_option(gbl, tkn))
		return ;
	free_all(gbl);
	if (gbl->hst && gbl->hst->data)
	{
		dllst_save(gbl->hst_path, gbl->hst);
		dllst_clear(&gbl->hst);
	}
	else if (gbl->hst)
		free(gbl->hst);
	trm_lstclear_gnl(0, &gbl->s_head);
	free(gbl->hst_path);
	tcsetattr(0, 0, &(gbl->old_term));
	exit_value = gbl->last_exit;
	free(gbl);
	exit(exit_value);
}
