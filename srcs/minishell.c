/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:32:40 by pramella          #+#    #+#             */
/*   Updated: 2020/06/16 02:30:00 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_exec(t_shell *sh)
{
	int ret;

	ret = 1;
	sh->line = NULL;
	while (ret == 1)
	{
		sh->cmd = NULL;
		ft_putstr_fd(tgetstr("vi", NULL), 1);
		display_prompt(sh->env);
		ft_putstr_fd(tgetstr("ve", NULL), 1);
		ret = trm_get_next_line(STDIN_FILENO, &sh->line, sh);
		(!sh->hst->data) ? (sh->hst->data = ft_strdup(sh->line)) :
						(sh->act_hst = dllst_add_back(&sh->hst, sh->line));
		ft_putstr_fd(tgetstr("vi", NULL), 1);
		sh->cmd = parsing(sh->line, sh->env, &sh->last_exit);
		free(sh->line);
		(sh->cmd) ? write(1, "\n", 1) : 0;
		ft_putstr_fd(tgetstr("ve", NULL), 1);
		execution(sh, sh->cmd);
		sh->spc->s = 0;
	}
}

int		main(int ac, char **av, char **ev)
{
	t_env	*tmp;
	t_shell	*sh;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_quit);
	sh = get_shell(INIT);
	sh->env = parse_env(ev);
	if ((tmp = get_env(sh->env, "HOME")))
		sh->hst_path = ft_strjoin(tmp->value, "/.minishell_history");
	sh->hst_on = 1;
	sh->act_hst = check_history(sh);
	sh->hst_on = 0;
	main_exec(sh);
	return (0);
}
