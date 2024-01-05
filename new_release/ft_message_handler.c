/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:54:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 12:30:53 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	initialize_message_handler(t_handler *message)
{
	message->fd_in = 0;
	message->fd_out = 0;
	message->in_error = 0;
	message->out_error = 0;
}

void	message_handler(int argc, char **argv, char **env, t_handler *message)
{
	initialize_message_handler(&message);
	message->fd_in = open(argv[1], O_RDONLY, 0777);
	message->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (message->fd_in == -1 && !access(argv[1], F_OK))
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	else if (message->fd_in == -1 && access(argv[1], F_OK))
	{
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	if (message->fd_out == -1 && !access(argv[4], F_OK))
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd("\n", 2);
	}
	else if (message->fd_out == -1 && access(argv[4], F_OK))
	{
		ft_putstr_fd("pipex: No such file or directory: ", 2);
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd("\n", 2);
	}


}
