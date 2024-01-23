/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/23 09:12:51 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_execute(char *path, char **env, char **commands)
{
	execve(path, commands, env);
	free(path);
	ft_free_substrings(commands);
	exit(EXIT_FAILURE);
}

static void	child_one(t_handler *message, int p_fd[], char **env)
{
	message->pid_one = fork();
	if (message->pid_one == -1)
		exit_handler(2, message);
	if (message->pid_one != 0)
		return ;
	if (message->in_error == 1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
	dup2(message->fd_in, 0);
	close(message->fd_in);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	close(p_fd[0]);
	free(message->path[1]);
	message->path[1] = NULL;
	ft_free_substrings(message->function_commands_two);
	if (message->fd_out != -1)
		close(message->fd_out);
	ft_execute(message->path[0], env, message->function_commands_one);
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
	ft_free_substrings(message->function_commands_one);
	if (message->fd_in != -1)
		close(message->fd_in);
	ft_execute(message->path[1], env, message->function_commands_two);
}

static void	forker_function(t_handler *message, char **env)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit_handler(1, message);
	if (message->in_error == 0)
	{
		child_one(message, p_fd, env);
	}
	if (message->out_error == 0)
	{
		message->pid_two = fork();
		if (message->pid_two == -1)
			exit_handler(2, message);
		if (message->pid_two == 0)
			child_two(message, p_fd, env);
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
	ft_bzero(&message, sizeof(t_handler));
	message_handler(argv, env, &message);
	forker_function(&message, env);
	if (message.in_error == 0)
		status = waiting_function(&message, message.pid_one,
				message.function_commands_one[0]);
	if (message.out_error == 0)
		status = waiting_function(&message, message.pid_two,
				message.function_commands_two[0]);
	if (status == 1)
		message.out_error = 126;
	ft_freeing_message(&message);
	return (message.out_error);
}
