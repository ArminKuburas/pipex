/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/20 11:20:44 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *function, char **env)
{
	char	**function_commands;
	char	*path;
	perror("ft_execute\n");

	function_commands = ft_pipex_split(function);
	path = ft_path_make(function_commands[0], env);
	if (execve(path, function_commands, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(function_commands[0], 2);
		ft_free_substrings(function_commands);
		free(path);
		exit(0);
	}
}

static void	child(char **argv, int p_fd[], char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	perror("child error\n");
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
	perror("parent error\n");
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
		exit(1);
	}
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child(argv, p_fd, env);
	else
		parent(argv, p_fd, env);
}
