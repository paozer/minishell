/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pminne <pminne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:27:09 by pramella          #+#    #+#             */
/*   Updated: 2020/05/07 00:25:02 by pminne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parent_code(int fd[2], pid_t pid)
{
	int		statlock;
	char	*line;

	line = NULL;
	waitpid(pid, &statlock, 0);
	if (WEXITSTATUS(statlock) == 0)
	{
		line = NULL;
		get_next_line(fd[0], &line);
	}
	close(fd[0]);
	close(fd[1]);
	return (line);
}

static void	child_code(int fd[2], char *path, char *av[])
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[1], STDERR_FILENO);
	close(fd[1]);
	close(fd[0]);
	execve(path, av, NULL);
	free(path);
	exit(1);
}

static char	*get_git_info(t_env *env, char *av[])
{
	pid_t	pid;
	int		fd[2];
	char	*path;
	char	*git_info;

	if (!(path = locate_executable(env, "git")))
		return (NULL);
	pipe(fd);
	pid = fork();
	git_info = NULL;
	if (pid == -1)
		return (NULL);
	else if (pid > 0)
		git_info = parent_code(fd, pid);
	else
		child_code(fd, path, av);
	free(path);
	return (git_info);
}

static char	*get_folder_name(t_env *env)
{
	t_env	*tmp;
	size_t	len;
	char	*subpath;
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_strdup("minishell"));
	len = ft_strlen(path);
	if (path[len - 1] == '/')
		subpath = ft_strdup("/");
	else if (path[0] == '/' && !ft_strchr(path + 1, '/'))
		subpath = ft_strdup(path);
	else if ((tmp = get_env(env, "HOME")) && len == ft_strlen(tmp->value) &&
			!ft_strncmp(path, tmp->value, len))
		subpath = ft_strdup("~");
	else if ((subpath = strrchr(path, '/')))
		subpath = ft_strdup(++subpath);
	else
		subpath = ft_strdup("minishell");
	free(path);
	return (subpath);
}

void		display_prompt(t_env *env)
{
	char		*folder;
	char		*git_info;
	static char	*av1[] = {"git", "symbolic-ref", "--short", "HEAD", NULL};
	static char	*av2[] = {"git", "rev-parse", "--short", "HEAD", NULL};

	folder = get_folder_name(env);
	git_info = get_git_info(env, av1);
	(!git_info) ? git_info = get_git_info(env, av2) : 0;
	ft_printf(CLR_GREEN"%s "CLR_RESET, folder);
	(git_info) ? ft_printf(CLR_CYAN"git:(%s) "CLR_RESET, git_info) : 0;
	free(folder);
	free(git_info);
}
