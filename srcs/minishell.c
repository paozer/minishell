/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:32:40 by pramella          #+#    #+#             */
/*   Updated: 2020/06/09 12:22:02 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_exec(t_all *gbl)
{
	int ret;

	ret = 1;
	gbl->line = NULL;
	while (ret == 1)
	{
		gbl->cmd = NULL;
		ft_putstr_fd(tgetstr("vi", NULL), 1);
		display_prompt(gbl->env);
		ft_putstr_fd(tgetstr("ve", NULL), 1);
		ret = trm_get_next_line(STDIN_FILENO, &gbl->line, gbl);
		(!gbl->hst->data) ? (gbl->hst->data = ft_strdup(gbl->line)) :
						(gbl->act_hst = dllst_add_back(&gbl->hst, gbl->line));
		ft_putstr_fd(tgetstr("vi", NULL), 1);
		gbl->cmd = parsing(gbl->line, gbl->env, &gbl->last_exit);
		free(gbl->line);
		(gbl->cmd) ? write(1, "\n", 1) : 0;
		ft_putstr_fd(tgetstr("ve", NULL), 1);
		execution(gbl, gbl->cmd);
		gbl->spc->s = 0;
	}
}

int		main(int ac, char **av, char **ev)
{
	t_env *tmp;
	t_all *gbl;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_quit);
	gbl = cp_gbl(INIT);
	gbl->env = parse_env(ev);
	if ((tmp = get_env(gbl->env, "HOME")))
		gbl->hst_path = ft_strjoin(tmp->value, "/.history");
	gbl->hst_on = 1;
	gbl->act_hst = check_history(gbl);
	gbl->hst_on = 0;
	main_exec(gbl);
	return (0);
}
