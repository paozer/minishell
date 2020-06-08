/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:40:16 by pminne            #+#    #+#             */
/*   Updated: 2020/05/07 00:24:27 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*init_left(void)
{
	char	*left;

	if (!(left = malloc(sizeof(*left) * 4)))
		return (NULL);
	left[0] = 27;
	left[1] = 91;
	left[2] = 68;
	left[3] = '\0';
	return (left);
}

static char	*init_right(void)
{
	char	*right;

	if (!(right = malloc(sizeof(*right) * 4)))
		return (NULL);
	right[0] = 27;
	right[1] = 91;
	right[2] = 67;
	right[3] = '\0';
	return (right);
}

static char	*init_up(void)
{
	char	*up;

	if (!(up = malloc(sizeof(*up) * 4)))
		return (NULL);
	up[0] = 27;
	up[1] = 79;
	up[2] = 65;
	up[3] = '\0';
	return (up);
}

t_trmkey	*init_termcap(void)
{
	t_trmkey	*trm_key;

	if (!(trm_key = malloc(sizeof(t_trmkey))))
		return (NULL);
	if (tgetent(NULL, "xterm-256color") <= 0)
		ft_printf("Error Loadin terminfo\n");
	trm_key->on = NULL;
	trm_key->on = tgetstr("ks", NULL);
	if (!trm_key->on)
		ft_printf("ERROR\n");
	trm_key->left = init_left();
	trm_key->right = init_right();
	trm_key->up = init_up();
	trm_key->save = tgetstr("sc", NULL);
	trm_key->reset = tgetstr("rc", NULL);
	trm_key->delk = tgetstr("bc", NULL);
	trm_key->del = tgetstr("dc", NULL);
	trm_key->clear = tgetstr("ce", NULL);
	trm_key->mov_csr = tgetstr("CM", NULL);
	return (trm_key);
}
