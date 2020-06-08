/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:32:40 by pramella          #+#    #+#             */
/*   Updated: 2020/06/05 23:09:42 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parses env char ** into env struct list (key:value:next)
** at program startup
*/

t_env	*parse_env(char **ev)
{
	size_t	i;
	size_t	ret;
	t_env	*env;
	t_env	*new;

	env = NULL;
	i = 0;
	while (ev[i])
	{
		ret = find_char(ev[i], '=');
		new = env_new(ft_substr(ev[i], 0, ret),
				ft_substr(ev[i], ret + 1, ft_strlen(ev[i] + ret + 1)), 1);
		env_add_back(&env, new);
		++i;
	}
	return (env);
}

t_all	*cp_gbl(int flg)
{
	static t_all	*gbl = NULL;

	if (flg == PULL)
		return (gbl);
	else if (flg == INIT)
	{
		if (!(gbl = malloc(sizeof(t_all))))
			exit(EXIT_FAILURE);
		init_terminal(gbl);
		gbl->hst_path = NULL;
		gbl->term_key = init_termcap();
		gbl->spc = init_cnt();
		gbl->last_exit = 0;
		return (NULL);
	}
	return (NULL);
}

void	main_exec(t_all *gbl)
{
	int ret;

	ret = 1;
	gbl->line = NULL;
	while (ret == 1)
	{
		gbl->cmd = NULL;
		ft_printf("%s", tgetstr("vi", NULL));
		display_prompt(gbl->env);
		ft_printf("%s", tgetstr("ve", NULL));
		ret = trm_get_next_line(STDIN_FILENO, &gbl->line,
			gbl);
		(!gbl->hst->data) ?
			(gbl->hst->data = ft_strdup(gbl->line)) :
			(gbl->act_hst =
				ft_dlstadd_back(&gbl->hst, gbl->line));
		ft_printf("%s", tgetstr("vi", NULL));
		gbl->cmd = parsing(gbl->line,
			gbl->env, &gbl->last_exit);
		(gbl->cmd) ? ft_printf("\n") : 0;
		ft_printf("%s", tgetstr("ve", NULL));
		execution(gbl, gbl->cmd);
		gbl->spc->s = 0;
	}
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av, char **ev)
{
	t_env	*tmp;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_quit);
	cp_gbl(INIT);
	cp_gbl(PULL)->env = parse_env(ev);
	if ((tmp = get_env(cp_gbl(PULL)->env, "HOME")))
		cp_gbl(PULL)->hst_path = ft_strjoin(tmp->value, "/.history");
	cp_gbl(PULL)->hst_on = 1;
	cp_gbl(PULL)->act_hst = check_history(cp_gbl(PULL));
	cp_gbl(PULL)->hst_on = 0;
	main_exec(cp_gbl(PULL));
	return (0);
}
