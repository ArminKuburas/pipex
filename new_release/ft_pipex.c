/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 15:08:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_execute(char *function, char **env)
{
	char	**function_commands;
	char	*path;

	function_commands = ft_pipex_split(function);
	path = ft_path_make(function_commands[0], env);
	if (execve(path, function_commands, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(function_commands[0], 2);
		ft_putstr_fd("\n", 2);
		ft_free_substrings(function_commands);
		free(path);
		exit(1);
	}
}

static void	child(char **argv, int p_fd[], char **env)
{

	dup2(fd, 0);
	close(fd);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	close(p_fd[0]);
	ft_execute(argv[2], env);
}

static void	child_two(char **argv, int p_fd[], char **env)
{

	dup2(fd, 1);
	close(fd);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	close(p_fd[1]);
	ft_execute(argv[3], env);
}

static int	ft_fork_twice(int pid1, char **argv, char **env, int *p_fd)
{
	pid_t	pid2;
	int		status;

	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		child_two(argv, p_fd, env);
	else
	{
		close(p_fd[0]);
		close(p_fd[1]);

	}
}

int	main(int argc, char *argv[], char **env)
{
	int			p_fd[2];
	pid_t		pid[2];
	t_handler	message;
	int			status;

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	message_handler(argc, argv, env, &message);
	if (pipe(p_fd) == -1)
		exit_handler(1);
	if (pid[0] == -1)
		exit_handler(2);
	if (pid[0] == 0)
		child(argv, p_fd, env, &message);
	forker_function(&message, pid, p_fd);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (message->signal_value);
}
