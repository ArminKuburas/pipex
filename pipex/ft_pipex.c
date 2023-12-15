/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/15 15:53:45 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *function, char **env)
{
	char	**function_commands;
	char	*path;

	function_commands = ft_pipex_split(function);
	path = ft_path_make(function_commands[0], env);
	
}

static void	child(char **argv, int p_fd[], char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		exit (-1);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	ft_execute(argv[2], env);
}

static void	parent(char **argv, int p_fd[], char **env)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit (-1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	ft_execute(argv[3], env);
}

int	main(int argc, char *argv[], char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		perror("./pipex file1 cmd cmd file2");
		exit(0);
	}
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child(argv[1], p_fd, env);
	else
		parent(argv[4], p_fd, env);
}
