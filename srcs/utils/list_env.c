/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:25:24 by pramella          #+#    #+#             */
/*   Updated: 2020/05/01 21:25:25 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Utilities used to handle the list of env variables and their values
*/

t_env	*env_new(char *key, char *value, int set)
{
	t_env *new;

	if (!(new = malloc(sizeof(*new))))
	{
		ft_fprintf(2, "minishell: malloc: %s\n", strerror(errno));
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->set = set;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **begin, t_env *new)
{
	t_env	*curr;

	if (!begin || !new)
		return ;
	if (!*begin)
	{
		*begin = new;
		new->next = NULL;
		return ;
	}
	curr = *begin;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->next = NULL;
}

int		env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		++i;
		env = env->next;
	}
	return (i);
}

/*
** Returns pointer to env struct if key is found
** key arg can have "key" or "key=value" format
*/

t_env	*get_env(t_env *env, char *key)
{
	size_t i;

	if (!env || !key)
		return (NULL);
	i = find_char(key, '=');
	while (env)
	{
		if (ft_strlen(env->key) == i && !ft_strncmp(env->key, key, i))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env *env, char *new_value)
{
	size_t i;

	i = find_char(new_value, '=');
	free(env->value);
	if (new_value[i] == '=')
		env->value = ft_substr(new_value, i + 1, ft_strlen(new_value + i + 1));
	else
		env->value = ft_strdup(new_value);
}
