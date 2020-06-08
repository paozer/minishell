/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:21:30 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:21:32 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** only check if (tkn)
*/

int		builtin_echo(t_list *tkn)
{
	int flag;

	if (tkn && !ft_strncmp(tkn->content, "-n", 3))
	{
		flag = 1;
		tkn = tkn->next;
	}
	else
		flag = 0;
	while (tkn)
	{
		write(1, tkn->content, ft_strlen(tkn->content));
		tkn = tkn->next;
		if (tkn && ((char *)tkn->content)[0])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
