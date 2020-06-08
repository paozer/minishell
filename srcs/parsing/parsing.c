/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:32:05 by pramella          #+#    #+#             */
/*   Updated: 2020/05/02 23:38:56 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_cmds(char *line, t_cmd **begin)
{
	size_t pos;
	size_t end;

	pos = 0;
	while (line[pos])
	{
		while (ft_isspace(line[pos]))
			++pos;
		if (!line[pos])
			return ;
		cmd_add_back(begin,
				ft_substr(line, pos, get_non_escaped(line, pos, "\t ;") - pos));
		end = get_non_escaped(line, pos, ";");
		while (pos < end)
		{
			pos = get_non_escaped(line, pos, "\t ;") + 1;
			while (pos < end && ft_isspace(line[pos]))
				++pos;
			if (pos < end)
				tkn_add_back(begin, ft_substr(line, pos,
							get_non_escaped(line, pos, "\t ;") - pos));
		}
		pos = (line[end]) ? end + 1 : end;
	}
}

void	parse_special_char(t_cmd *cmd, char *charset,
		void (*found)(t_cmd *, t_list *, int))
{
	int		ret;
	t_list	*tkn;

	while (cmd)
	{
		ret = 0;
		tkn = cmd->token;
		while (tkn && (ret == 0 || ((char *)tkn->content)[ret]))
		{
			ret = get_non_escaped(tkn->content, ret, charset);
			if (!((char *)tkn->content)[ret])
			{
				ret = 0;
				tkn = tkn->next;
			}
			else if (ft_isinset(((char *)tkn->content)[ret], charset))
				(*found)(cmd, tkn, ret);
		}
		cmd = cmd->next;
	}
}

t_cmd	*parsing(char *line, t_env *env, int *last_exit)
{
	t_cmd *cmd;

	if (!valid_syntax(line))
	{
		free(line);
		*last_exit = 258;
		return (NULL);
	}
	cmd = NULL;
	split_cmds(line, &cmd);
	free(line);
	parse_dollar(cmd, env, *last_exit);
	parse_special_char(cmd, "|", parse_pipe);
	parse_special_char(cmd, "<>", parse_redirect);
	rm_parsed_redirects(cmd);
	rm_quotes(cmd);
	return (cmd);
}
