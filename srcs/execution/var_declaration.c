/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_declaration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:34:51 by pramella          #+#    #+#             */
/*   Updated: 2020/05/06 17:33:32 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_var_declaration(char *str)
{
	size_t i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	if (str[i] != '=')
		return (0);
	else
		++i;
	while (ft_isalnum(str[i]) || ft_isinset(str[i], "_-:./;"))
		++i;
	if (str[i])
		return (0);
	return (1);
}

static int	handle_logic(t_list *tkn, t_env *env, t_env **new)
{
	size_t	i;
	t_env	*tmp;

	if (!is_var_declaration(tkn->content))
	{
		free_env(*new);
		return (1);
	}
	else if ((tmp = get_env(env, tkn->content)) ||
			(tmp = get_env(*new, tkn->content)))
		set_env_value(tmp, tkn->content);
	else
	{
		i = find_char(tkn->content, '=');
		tmp = env_new(ft_substr(tkn->content, 0, i), ft_substr(
			tkn->content, i + 1, ft_strlen(tkn->content + i + 1)), 0);
		env_add_back(new, tmp);
	}
	return (0);
}

/*
** If var is already in env list the value is always changed
*/

void		parse_var_declaration(t_cmd *cmd, t_list **tk, t_env *env)
{
	t_list	*tkn;
	t_env	*new;

	tkn = cmd->token;
	new = NULL;
	while (tkn)
	{
		if (handle_logic(tkn, env, &new))
		{
			*tk = tkn;
			return ;
		}
		tkn = tkn->next;
	}
	ft_lstclear(&cmd->token, &free);
	cmd->token = NULL;
	*tk = NULL;
	env_add_back(&env, new);
}
