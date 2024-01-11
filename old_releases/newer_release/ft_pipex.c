/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/10 14:29:06 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include <stdio.h>

static void	ft_execute(char *path, char *function, char **env)
{
	char	**function_commands;

	function_commands = ft_pipex_split(function);
	ft_printf("%s\n", path);
	ft_printf("%s\n", function);
	ft_printf("%s\n", function_commands[0]);
	if (execve(path, function_commands, env) == -1)
	{
		if (function_commands[1] == NULL)
		exit(1);
	}
}

static void	child_one(t_handler *message, char **argv, int p_fd[], char **env)
{
	dup2(message->fd_in, 0);
	close(message->fd_in);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	close(p_fd[0]);
	ft_execute(message->path[0], argv[2], env);
	exit(1);
}

static void	child_two(t_handler *message, char **argv, int p_fd[], char **env)
{
	dup2(message->fd_out, 1);
	close(message->fd_out);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	close(p_fd[1]);
	ft_execute(message->path[1], argv[3], env);
	exit(1);
}

static void	forker_function(t_handler *message, char **env, char **argv)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit_handler(1);
	message->pid_one = fork();
	if (message->pid_one == -1)
		exit_handler(2);
	else if (message->pid_one == 0)
	{
		if (message->in_error == 1)
			in_error_handler(p_fd);
		child_one(message, argv, p_fd, env);
	}
	else if (message->out_error == 0)
	{
		message->pid_two = fork();
		if (message->pid_two == -1)
			exit_handler(2);
		else if (message->pid_two == 0)
			child_two(message, argv, p_fd, env);
	}
	close(p_fd[0]);
	close(p_fd[1]);
}

int	main(int argc, char *argv[], char **env)
{
	t_handler	message;
	int			status;

	status = 0;
	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	message.function_commands_one = ft_pipex_split(argv[2]);
	message.function_commands_two = ft_pipex_split(argv[3]);
	message_handler(argv, env, &message);
	forker_function(&message, env, argv);
	if (waitpid(message.pid_one, &status, 0) == -1)
	{
		exit(1);
	}
	if (message.out_error != 0)
		return (message.out_error);
	if (waitpid(message.pid_two, &status, 0) == -1)
	{
		exit(1);
	}
	return (0);
}
