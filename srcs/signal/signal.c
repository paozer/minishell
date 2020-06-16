/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:27:55 by pminne            #+#    #+#             */
/*   Updated: 2020/06/16 02:27:37 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the get_shell function gives access to the global structure in parts of the
** program where the struct cannot be passed as an argument.
** signal handling, get_next_line and history_checking functions
*/

t_shell	*get_shell(int flag)
{
	static t_shell *sh = NULL;

	if (flag == PULL)
		return (sh);
	else if (flag == INIT)
	{
		if (!(sh = malloc(sizeof(t_shell))))
			exit(EXIT_FAILURE);
		init_terminal(sh);
		sh->hst_path = NULL;
		sh->term_key = init_termcap();
		sh->spc = init_cnt();
		sh->last_exit = 0;
		return (sh);
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
	t_shell *sh;

	(void)sig;
	sh = get_shell(PULL);
	ft_putstr_fd("^C\n", 1);
	signal(SIGINT, sig_main);
	free(sh->spc);
	sh->spc = init_cnt();
	free(sh->line);
	sh->line = NULL;
	display_prompt(sh->env);
}
