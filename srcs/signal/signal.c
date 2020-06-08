/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:27:55 by pminne            #+#    #+#             */
/*   Updated: 2020/06/05 18:25:05 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_child(int sig)
{
	static int pid;

	if (pid)
	{
		kill(pid, sig);
		if (sig == SIGQUIT)
			ft_printf("Quitter (core dumped)\n");
		else if (sig == SIGINT || sig == SIGQUIT)
			ft_printf("\n");
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
	(void)sig;
	write(1, "^C\n", 3);
	signal(SIGINT, sig_main);
	free(cp_gbl(PULL)->spc);
	cp_gbl(PULL)->spc = init_cnt();
	free(cp_gbl(PULL)->line);
	cp_gbl(PULL)->line = NULL;
	display_prompt(cp_gbl(PULL)->env);
}
