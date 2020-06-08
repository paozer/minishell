/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:09:23 by pminne            #+#    #+#             */
/*   Updated: 2020/05/05 19:10:01 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_terminal(t_all *gbl)
{
	tcgetattr(0, &(gbl->old_term));
	tcgetattr(0, &(gbl->new_term));
	gbl->new_term.c_lflag &= ~(ICANON);
	gbl->new_term.c_lflag &= ~(ECHO);
	gbl->new_term.c_cc[VMIN] = 1;
	gbl->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(gbl->new_term));
}

t_cnt	*init_cnt(void)
{
	t_cnt *ret;

	if (!(ret = malloc(sizeof(*ret))))
		return (NULL);
	ret->s = 0;
	ret->save = NULL;
	return (ret);
}

int		is_only_whitespace(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
