/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:28:29 by pramella          #+#    #+#             */
/*   Updated: 2020/06/06 15:09:38 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(t_cmd *cmd)
{
	if (cmd->std_in == PIPE)
		cmd->fd_copy_in = dup(STDIN_FILENO);
	if (cmd->std_out == PIPE)
	{
		pipe(cmd->p_out);
		cmd->fd_copy_out = dup(STDOUT_FILENO);
	}
	if (cmd->std_in == REDIRECT)
		set_redirect_fd(cmd, STDIN_FILENO);
	if (cmd->std_out == REDIRECT)
		set_redirect_fd(cmd, STDOUT_FILENO);
	if (cmd->next && cmd->std_out != PIPE && cmd->next->std_in == PIPE)
	{
		pipe(cmd->p_out);
		cmd->next->p_in[0] = cmd->p_out[0];
		cmd->next->p_in[1] = cmd->p_out[1];
		close(cmd->p_out[1]);
	}
}

void	reset_fd(t_cmd *cmd)
{
	if (cmd->std_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_copy_out, STDOUT_FILENO);
		close(cmd->fd_copy_out);
	}
	if (cmd->std_in != STDIN_FILENO)
	{
		dup2(cmd->fd_copy_in, STDIN_FILENO);
		close(cmd->fd_copy_in);
	}
}

void	handle_builtins(t_all *gbl, t_cmd *cmd, t_list *tkn)
{
	set_builtin_pipe(cmd);
	if (!ft_strncmp(tkn->content, "cd", 3))
		gbl->last_exit = builtin_cd(gbl->env, tkn->next);
	else if (!ft_strncmp(tkn->content, "echo", 5))
		gbl->last_exit = builtin_echo(tkn->next);
	else if (!ft_strncmp(tkn->content, "env", 4))
		gbl->last_exit = builtin_env(gbl->env);
	else if (!ft_strncmp(tkn->content, "exit", 5))
		builtin_exit(gbl, tkn->next);
	else if (!ft_strncmp(tkn->content, "export", 7))
		gbl->last_exit = builtin_export(gbl->env, tkn->next);
	else if (!ft_strncmp(tkn->content, "pwd", 4))
		gbl->last_exit = builtin_pwd();
	else if (!ft_strncmp(tkn->content, "unset", 6))
		gbl->last_exit = builtin_unset(&gbl->env, tkn->next);
}

/*
** Locates executable in absolute, relativ or PATH paths.
*/

char	*locate_executable(t_env *env, char *name)
{
	int			i;
	char		**split;
	char		*path;
	char		*s;
	struct stat	buf;

	if (stat(name, &buf) == 0 && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
		return (ft_strdup(name));
	if (!(env = get_env(env, "PATH")))
		return (NULL);
	i = -1;
	path = NULL;
	split = ft_split(env->value, ":");
	while (split && split[++i])
	{
		s = ft_strjoin(split[i], "/");
		path = ft_strjoin(s, name);
		free(s);
		if (!stat(path, &buf) && buf.st_mode & S_IXUSR && !S_ISDIR(buf.st_mode))
			break ;
		free(path);
		path = NULL;
	}
	ft_split_free(split);
	return (path);
}

void	execution(t_all *gbl, t_cmd *cmd)
{
	char	*path;

	while (cmd)
	{
		if (cmd->token && is_var_declaration(cmd->token->content))
			parse_var_declaration(cmd, &(cmd->token), gbl->env);
		set_fd(cmd);
		if (cmd->token && cmd->std_in != -1)
		{
			if (is_builtin(cmd->token->content))
				handle_builtins(gbl, cmd, cmd->token);
			else if (!(path = locate_executable(gbl->env, cmd->token->content)))
			{
				ft_fprintf(2, "minishell: %s: command not found\n",
						(char *)cmd->token->content);
				gbl->last_exit = 127;
			}
			else
				handle_execve(gbl, cmd, path);
		}
		reset_fd(cmd);
		cmd = cmd->next;
	}
	free_cmd(gbl->cmd);
}
