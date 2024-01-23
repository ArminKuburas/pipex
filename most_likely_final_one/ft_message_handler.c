/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:54:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/23 02:07:20 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	message_opener(char **argv, t_handler *message)
{
	message->fd_in = open(argv[1], O_RDONLY, 0777);
	message->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (message->fd_in == -1 && !access(argv[1], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(13), argv[1]);
		message->in_error = 1;
	}
	else if (message->fd_in == -1 && access(argv[1], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(2), argv[1]);
		message->in_error = 1;
	}
	if (message->fd_out == -1 && !access(argv[4], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(13), argv[4]);
		message->out_error = 1;
	}
	else if (message->fd_out == -1 && access(argv[4], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(2), argv[4]);
		message->out_error = 127;
	}
}

void	dir_check(t_handler *message, char *command, int in_out)
{
	int	temp_fd;

	temp_fd = 0;
	handle_access(command, message);
	if (message->path_error == 2)
	{
		temp_fd = open(command, O_DIRECTORY);
		if (temp_fd != -1)
		{
			close(temp_fd);
			ft_printf("pipex: permission denied: %s\n", command);
		}
		if (temp_fd != -1 && in_out == 1)
			message->in_error = 1;
		else if (temp_fd != -1 && in_out == 2)
			message->out_error = 126;
	}
}

void	message_handler(char **argv, char **env, t_handler *message)
{
	message_opener(argv, message);
	if (argv[2][0] != '\0')
		message->function_commands_one = ft_pipex_split(argv[2], message);
	else
		path_error_handler(argv[2], message, 1);
	if (argv[3][0] != '\0')
		message->function_commands_two = ft_pipex_split(argv[3], message);
	else
		path_error_handler(argv[3], message, 2);
	if (message->in_error == 0)
		dir_check(message, message->function_commands_one[0], 1);
	if (message->out_error == 0)
		dir_check(message, message->function_commands_two[0], 2);
	if (message->in_error == 0)
		path_maker(env, message, message->function_commands_one[0], 0);
	if (message->out_error == 0)
		path_maker(env, message, message->function_commands_two[0], 1);
}
