/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:36:13 by pramella          #+#    #+#             */
/*   Updated: 2020/06/05 20:14:36 by pramella         ###   ########lyon.fr   */
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

static void	replace_env(char **s, int ret, char *env)
{
	size_t	i;
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = ft_substr(*s, 0, ret);
	s2 = (!env) ? "" : env;
	i = 0;
	if (ft_isdigit((*s + ret + 1)[i]) || ft_isinset(*(*s + ret + 1), "!"))
		++i;
	else
		while (ft_isalnum((*s + ret + 1)[i]) || *(*s + ret + 1 + i) == '_')
			++i;
	s3 = ft_substr(*s + ret + 1, i, ft_strlen(*s + ret + 1 + i));
	free(*s);
	*s = ft_strjoin(s1, s2);
	s2 = *s;
	*s = ft_strjoin(*s, s3);
	free(s1);
	free(s2);
	free(s3);
}

static void	search_replace_env(char **s, int ret, t_env *env)
{
	size_t	i;
	t_env	*tmp;
	char	*sub;

	if (ft_isdigit(*(*s + ret + 1)) || ft_isinset(*(*s + ret + 1), "!"))
		i = 2;
	else
	{
		i = 1;
		while (ft_isalnum(*(*s + ret + i)) || *(*s + ret + i) == '_')
			++i;
	}
	sub = ft_substr(*s, ret + 1, --i);
	if ((tmp = get_env(env, sub)))
		replace_env(s, ret, tmp->value);
	else
		replace_env(s, ret, NULL);
	free(sub);
}

/*
** looks up unescaped $ in tokens
** calls fct that searches the var and replaces it
**
** $[alphanum] is replaced by env var value if it exists or nothing
** $? is replaced by the last commands exit status
** $$ is not replaced
*/

static void	handle_logic(t_list *tkn, t_env *env, int ret, int last_exit)
{
	char *str;

	str = tkn->content;
	if (str[ret + 1] == '?')
	{
		((char *)tkn->content)[ret + 1] = '0';
		str = ft_itoa(last_exit);
		replace_env(((char **)&tkn->content), ret, str);
		free(str);
	}
	else
		search_replace_env((char **)&tkn->content, ret, env);
}

void		parse_dollar(t_cmd *cmd, t_env *env, int last_exit)
{
	int		ret;
	char	*str;
	t_list	*tkn;

	while (cmd)
	{
		tkn = cmd->token;
		ret = 0;
		while (tkn)
		{
			str = (char *)tkn->content;
			ret = get_non_escaped2(tkn->content, ret, "$");
			if (str[ret])
			{
				if (!str[ret + 1] || str[ret + 1] == '$' || str[ret + 1] == '"')
					++ret;
				else
					handle_logic(tkn, env, ret, last_exit);
				continue ;
			}
			ret = 0;
			tkn = tkn->next;
		}
		cmd = cmd->next;
	}
}
