/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/09 02:19:09 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_free_substrings(char **arr_str)
{
	int	i;

	i = 0;
	while (arr_str[i])
	{
		free(arr_str[i]);
		arr_str[i] = NULL;
		i++;
	}
	free(arr_str);
	arr_str = NULL;
}

void	path_error_handler(char *function, t_handler *message, int type)
{
	if (type == 1 && message->in_error != 1)
	{
		ft_printf("pipex: %s %s\n", strerror(13), function);
		message->in_error = 1;
	}
	else if (type == 2 && message->out_error == 0)
	{
		ft_printf("pipex: %s %s\n", strerror(13), function);
		message->out_error = 126;
	}
	else if (type == 3 && message->in_error != 1)
	{
		ft_printf("pipex: command not found: %s\n", function);
		message->in_error = 1;
	}
	else if (type == 4 && message->out_error == 0)
	{
		ft_printf("pipex: command not found: %s\n", function);
		message->out_error = 127;
	}
}

void	exit_handler(int type)
{
	if (type == 1)
	{
		
	}
}
