/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:31:42 by pramella          #+#    #+#             */
/*   Updated: 2020/05/03 14:59:36 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *token)
{
	int			i;
	static char	*builtin[8] = {"cd", "echo", "env", "exit",
								"export", "pwd", "unset", NULL};

	if (!token)
		return (0);
	i = 0;
	while (builtin[i])
	{
		if (!ft_strncmp(token, builtin[i], ft_strlen(builtin[i]) + 1))
			return (1);
		++i;
	}
	return (0);
}
