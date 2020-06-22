/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:40:16 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:24:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_key(int key)
{
	static char up[] = {27, 79, 65, 0};
	static char right[] = {27, 91, 67, 0};
	static char left[] = {27, 91, 68, 0};

	if (key == 0)
		return (up);
	if (key == 1)
		return (right);
	if (key == 2)
		return (left);
	return (NULL);
}

t_trmkey	*init_termcap(void)
{
	t_trmkey	*trm_key;

	if (!(trm_key = malloc(sizeof(t_trmkey))))
		return (NULL);
	if (tgetent(NULL, "xterm-256color") <= 0)
		write(2, "minishell: Error Loading terminfo\n", 34);
	trm_key->on = NULL;
	if (!(trm_key->on = tgetstr("ks", NULL)))
		write(2, "minishell: Error\n", 17);
	trm_key->up = init_key(0);
	trm_key->right = init_key(1);
	trm_key->left = init_key(2);
	trm_key->save = tgetstr("sc", NULL);
	trm_key->reset = tgetstr("rc", NULL);
	trm_key->delk = tgetstr("bc", NULL);
	trm_key->del = tgetstr("dc", NULL);
	trm_key->clear = tgetstr("ce", NULL);
	trm_key->mov_csr = tgetstr("CM", NULL);
	return (trm_key);
}

void		init_terminal(t_shell *sh)
{
	tcgetattr(0, &(sh->old_term));
	tcgetattr(0, &(sh->new_term));
	sh->new_term.c_lflag &= ~(ICANON);
	sh->new_term.c_lflag &= ~(ECHO);
	sh->new_term.c_cc[VMIN] = 1;
	sh->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(sh->new_term));
}

t_cnt		*init_cnt(void)
{
	t_cnt *ret;

	if (!(ret = malloc(sizeof(*ret))))
		return (NULL);
	ret->s = 0;
	ret->save = NULL;
	return (ret);
}

int			is_only_whitespace(char *line)
{
	size_t i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		++i;
	}
	return (1);
}
