/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/17 12:12:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_execute(t_handler *msg, char *path, char **env, char **commands)
{
	execve(path, commands, env);
	free(path);
	ft_free_substrings(&(commands));
	exit(EXIT_FAILURE);
}

static void	child_one(t_handler *message, int p_fd[], char **env, char **argv)
{
	dup2(message->fd_in, 0);
	close(message->fd_in);
	dup2(p_fd[1], 1);
	close(p_fd[1]);
	close(p_fd[0]);
	free(message->path[1]);
	message->path[1] = NULL;
	ft_execute(message, message->path[0], env, argv[2]);
}

static void	child_two(t_handler *message, int p_fd[], char **env, char **argv)
{
	dup2(message->fd_out, 1);
	close(message->fd_out);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	close(p_fd[1]);
	free(message->path[0]);
	message->path[0] = NULL;
	ft_execute(message, message->path[1], env, argv[3]);
}

static void	forker_function(t_handler *message, char **env, char **argv)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit_handler(1, message);
	message->pid_one = fork();
	if (message->pid_one == -1)
		exit_handler(2, message);
	else if (message->pid_one == 0)
	{
		if (message->in_error == 1)
			in_error_handler(p_fd);
		child_one(message, p_fd, env, argv);
	}
	else if (message->out_error == 0)
	{
		message->pid_two = fork();
		if (message->pid_two == -1)
			exit_handler(2, message);
		else if (message->pid_two == 0)
			child_two(message, p_fd, env, argv);
	}
	close(p_fd[0]);
	close(p_fd[1]);
}

void	waiting_function(t_handler *message)
{
	int	status;

	if (message->in_error != 1)
	{
		if (waitpid(message->pid_one, &status, 0) == -1)
		{
			exit_handler(3, message);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			ft_printf("pipex: exec format error: %s\n",
				message->function_commands_one[0]);
		}
	}
	if (message->out_error != 0)
		return ;
	if (waitpid(message->pid_two, &status, 0) == -1)
		exit_handler(3, message);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		ft_printf("pipex: exec format error: %s\n",
			message->function_commands_two[0]);
		message->out_error = 126;
	}
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
	message.function_commands_one = ft_pipex_split(argv[2], &message);
	message.function_commands_two = ft_pipex_split(argv[3], &message);
	message_handler(argv, env, &message);
	ft_free_substrings(&(message.function_commands_one));
	ft_free_substrings(&(message.function_commands_two));
	forker_function(&message, env, argv);
	waiting_function(&message);
	ft_freeing_message(&message);
	return (message.out_error);
}
