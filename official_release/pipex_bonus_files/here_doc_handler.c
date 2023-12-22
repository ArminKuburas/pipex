/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 20:43:09 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/22 15:52:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	here_doc_in(char **argv, int *p_fd)
{
	char	*line;

	close (p_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, p_fd[1]);
		free(line);
	}
}

void	here_doc_handler(char **argv, int argc, int *fd_out)
{
	int		p_fd[2];
	pid_t	pid;

	if (argc < 6)
		exit_handler(2);
	*fd_out = handle_file(argv[argc - 1], 2);
	if (pipe (p_fd) == -1)
		exit(0);
	pid = fork();
	if (!pid)
		here_doc_in(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}
