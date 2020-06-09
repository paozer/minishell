/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:27:55 by pminne            #+#    #+#             */
/*   Updated: 2020/06/09 13:33:45 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the cp_gbl function gives access to the global structure in parts of the
** program where the struct cannot be passed as an argument.
** signal handling, get_next_line and history_checking functions
*/

t_all	*cp_gbl(int flag)
{
	static t_all *gbl = NULL;

	if (flag == PULL)
		return (gbl);
	else if (flag == INIT)
	{
		if (!(gbl = malloc(sizeof(t_all))))
			exit(EXIT_FAILURE);
		init_terminal(gbl);
		gbl->hst_path = NULL;
		gbl->term_key = init_termcap();
		gbl->spc = init_cnt();
		gbl->last_exit = 0;
		return (gbl);
	}
	return (NULL);
}

void	sig_child(int sig)
{
	static int pid;

	if (pid)
	{
		kill(pid, sig);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quitter (core dumped)\n", 1);
		else if (sig == SIGINT || sig == SIGQUIT)
			ft_putstr_fd("\n", 1);
		pid = 0;
	}
	else
		pid = sig;
}

void	sig_quit(int sig)
{
	sig = 0;
	signal(SIGQUIT, sig_quit);
}

void	sig_main(int sig)
{
	t_all *gbl;

	(void)sig;
	gbl = cp_gbl(PULL);
	ft_putstr_fd("^C\n", 1);
	signal(SIGINT, sig_main);
	free(gbl->spc);
	gbl->spc = init_cnt();
	free(gbl->line);
	gbl->line = NULL;
	display_prompt(gbl->env);
}
