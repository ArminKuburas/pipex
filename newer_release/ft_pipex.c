/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/15 18:58:37 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_execute(t_handler *message, char **env, int in_out)
{
	if (in_out == 1)
	{
		execve(message->path[0], message->function_commands_one, env);
		ft_printf("pipex: %s: %s\n", strerror(errno), \
			message->function_commands_one[0]);
	}
	else if (in_out == 2)
	{
		execve(message->path[1], message->function_commands_two, env);
		ft_printf("pipex: %s: %s\n", strerror(errno), \
			message->function_commands_two[0]);
	}
	ft_freeing_message(message);
	exit(-1);
}

static void	child_one(t_handler *message, int p_fd[], char **env)
{
	dup2(message->fd_in, 0);
	close(message->fd_in);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	close(p_fd[0]);
	free(message->path[1]);
	message->path[1] = NULL;
	ft_free_substrings(&(message->function_commands_two));
	ft_execute(message, env, 1);
}

static void	child_two(t_handler *message, int p_fd[], char **env)
{
	dup2(message->fd_out, 1);
	close(message->fd_out);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	close(p_fd[1]);
	free(message->path[0]);
	message->path[0] = NULL;
	ft_free_substrings(&(message->function_commands_one));
	ft_execute(message, env, 2);
}

static void	forker_function(t_handler *message, char **env)
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
		child_one(message, p_fd, env);
	}
	else if (message->out_error == 0)
	{
		message->pid_two = fork();
		if (message->pid_two == -1)
			exit_handler(2);
		else if (message->pid_two == 0)
			child_two(message, p_fd, env);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	ft_freeing_message(message);
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
	forker_function(&message, env);
	if (waitpid(message.pid_one, &status, 0) == -1)
	{
		exit_handler(3);
	}
	if (message.out_error != 0)
		return (message.out_error);
	if (waitpid(message.pid_two, &status, 0) == -1)
	{
		exit_handler(3);
	}
	return (0);
}
