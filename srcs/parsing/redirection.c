/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:36:55 by pramella          #+#    #+#             */
/*   Updated: 2020/06/04 17:06:58 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** handles unescaped redirections found in the tokens of a command
**
** @arg: cmd where redirection was found
** @arg: token where redirection was found
** @arg: index where redirection was found
**
** if handles redirect char and filename in diff tokens
** else handles redirect char and file in same token
*/

void	parse_redirect(t_cmd *cmd, t_list *token, int ret)
{
	t_list **file;

	cmd->append = (((char *)token->content)[ret] == '>' &&
					((char *)token->content)[ret + 1] == '>') ? 1 : 0;
	(((char *)token->content)[ret] == '>') ? (cmd->std_out = REDIRECT)
											: (cmd->std_in = REDIRECT);
	file = (((char *)token->content)[ret] == '>') ?
		&cmd->file_out : &cmd->file_in;
	if (!((char *)token->content)[ret + 1] ||
		(((char *)token->content)[ret + 1] == '>' &&
		!((char *)token->content)[ret + 2]))
	{
		ft_lstadd_back(file, ft_lstnew(ft_strdup(token->next->content)));
		ft_bzero(token->next->content + ret,
			ft_strlen(token->next->content + ret));
	}
	else
	{
		ret += (cmd->append == 1) ? 2 : 1;
		(((char *)token->content)[ret] == '>') ? ++ret : 0;
		ft_lstadd_back(file, ft_lstnew(ft_substr(token->content, ret,
			ft_strlen(token->content + ret))));
		ret -= (cmd->append == 1) ? 2 : 1;
	}
	ft_bzero(token->content + ret, ft_strlen(token->content + ret));
}

/*
** handles unescaped pipes found in the tokens of a command
**
** @arg: cmd where pipe was found
** @arg: token where pipe was found
** @arg: index where pipe was found
**
** if handles pipe char and filename in diff tokens
** else handles pipe char and file in same token
*/

void	parse_pipe(t_cmd *cmd, t_list *tkn, int ret)
{
	t_cmd *new;

	new = cmd_new();
	if (!((char *)tkn->content)[ret + 1])
	{
		tkn_add_back(&new, ft_strdup(tkn->next->content));
		((char *)tkn->content)[ret] = '\0';
		new->token->next = tkn->next->next;
		free(tkn->next->content);
		free(tkn->next);
	}
	else
	{
		tkn_add_back(&new, ft_substr(tkn->content, ret + 1,
					ft_strlen(tkn->content + ret + 1)));
		ft_bzero(tkn->content + ret, ft_strlen(tkn->content + ret));
		new->token->next = tkn->next;
	}
	tkn->next = NULL;
	new->next = cmd->next;
	cmd->next = new;
	new->std_in = PIPE;
	cmd->std_out = PIPE;
}
