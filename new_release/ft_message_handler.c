/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:54:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 18:06:58 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	initialize_message_handler(t_handler *message)
{
	message->fd_in = 0;
	message->fd_out = 0;
	message->in_error = 0;
	message->out_error = 0;
	message->signal_value = 0;
}

static void	access_checker(t_handler *message, char **argv, int argc)
{
	int	i;
	int	amount;

	i = 0;
	amount = argc - 2;
	while (amount > 0)
	{
		if (access(argv[amount], F_OK) == 0)
		{
			if (access(argv[amount], X_OK) == 0)
				message->values[i] = 0;
			else
				message->values[i] = 2;
		}
		else
			message->values[i] = 1;
		amount--;
		i++;
	}
}

void	message_handler(int argc, char **argv, char **env, t_handler *message)
{
	initialize_message_handler(&message);
	message->fd_in = open(argv[1], O_RDONLY, 0777);
	message->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (message->fd_in == -1 && !access(argv[1], F_OK))
		ft_printf("pipex: %s %s\n", strerror(13), argv[1]);
	else if (message->fd_in == -1 && access(argv[1], F_OK))
		ft_printf("pipex: %s %s\n", strerror(2), argv[1]);
	if (message->fd_out == -1 && !access(argv[4], F_OK))
	{
		ft_printf("pipex: %s %s\n", strerror(13), argv[4]);
		message->signal_value = 1;
		exit(1);
	}
	else if (message->fd_out == -1 && access(argv[4], F_OK))
	{
		ft_printf("pipex: %s %s\n", strerror(2), argv[4]);
		message->signal_value = 127;
		exit(127);
	}
	command_access_check(&message, argv, argc);
	ft_path_make(&message, argv, env, argc);
}
