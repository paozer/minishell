/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:32:27 by pramella          #+#    #+#             */
/*   Updated: 2020/06/06 15:10:19 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_cmd *cmd, t_list *file, int std_fd)
{
	int fd;

	fd = -1;
	if (std_fd == STDOUT_FILENO)
	{
		if (cmd->append)
			fd = open(file->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (std_fd == STDIN_FILENO)
		fd = open(file->content, O_RDONLY);
	return (fd);
}

void		set_redirect_fd(t_cmd *cmd, int std_fd)
{
	int		fd;
	t_list	*file;

	file = (std_fd == STDIN_FILENO) ? cmd->file_in : cmd->file_out;
	(std_fd == STDIN_FILENO) ? (cmd->fd_copy_in = dup(std_fd)) :
		(cmd->fd_copy_out = dup(std_fd));
	while (file)
	{
		if ((fd = open_file(cmd, file, std_fd)) == -1)
		{
			ft_fprintf(2, "minishell: %s: %s\n",
				(char *)file->content, strerror(errno));
			cmd->std_in = -1;
			return ;
		}
		file = file->next;
		(file) ? close(fd) : 0;
	}
	dup2(fd, std_fd);
	close(fd);
}
