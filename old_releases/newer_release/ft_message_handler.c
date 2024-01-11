/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:54:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/10 07:56:12 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	initialize_message_handler(t_handler *message)
{
	message->fd_in = 0;
	message->fd_out = 0;
	message->in_error = 0;
	message->out_error = 0;
	message->path_error = 0;
}

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

void	message_handler(char **argv, char **env, t_handler *message)
{
	initialize_message_handler(message);
	message_opener(argv, message);
	function_path_maker(argv, env, message);
}
