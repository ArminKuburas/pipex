/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/18 16:56:15 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_opener(t_pipex *info, char **argv)
{
	info->fds[0] = open(argv[1], O_RDONLY, 0777);
	info->fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->fds[0] == -1 && !access(argv[1], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(13), argv[1]);
		info->error[0] = 1;
	}
	else if (info->fds[0] == -1 && access(argv[1], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(2), argv[1]);
		info->error[0] = 1;
	}
	if (info->fds[1] == -1 && !access(argv[((info->amount) + 1)], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(13), argv[4]);
		info->error[(info->amount)] = 1;
	}
	else if (info->fds[] == -1 && access(argv[4], F_OK))
	{
		ft_printf("pipex: %s: %s\n", strerror(2), argv[4]);
		info->error[(info->amount)] = 127;
	}
}

int	access_check(char *str)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
			return (2);
		return (1);
	}
	return (0);
}

void	set_up_info(t_pipex *info, int argc, char **argv, char **env)
{
	int	i;

	info->amount = argc - 3;
	info->error = (int *)ft_calloc(info->amount, sizeof(int));
	if (!(info->error))
		handle_error(info, 1);
	info->path = (char **)malloc(info->amount * sizeof(char *));
	if (!(iinfo->path))
		handle_error(info, 1);
	info->commands = (char ***)malloc(info->amount * sizeof(char **));
	if (!(info->commands))
		handle_error(info, 1);
	file_opener(info, argv);
	i = 0;
	while (i < info->amount)
	{
		if (info->error[i] == 0)
			path_maker(info, i, argv, env);
		i++;
	}
}
