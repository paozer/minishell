/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:32:16 by pramella          #+#    #+#             */
/*   Updated: 2020/06/03 22:35:03 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_read_write_pipe(t_cmd *cmd)
{
	if (cmd->std_in != PIPE || cmd->std_out != STDOUT_FILENO)
	{
		dup2(cmd->p_out[1], STDOUT_FILENO);
		close(cmd->p_out[0]);
		close(cmd->p_out[1]);
	}
	if (cmd->std_in != STDIN_FILENO || cmd->std_out != PIPE)
	{
		dup2(cmd->p_in[0], STDIN_FILENO);
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
}

void	set_cmd_pipe(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
	{
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
	if (cmd->std_out == PIPE)
	{
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
	}
}

void	set_builtin_pipe(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
	{
		dup2(cmd->p_in[0], STDIN_FILENO);
		close(cmd->p_in[0]);
		close(cmd->p_in[1]);
	}
	if (cmd->std_out == PIPE)
	{
		dup2(cmd->p_out[1], STDOUT_FILENO);
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
	}
}
