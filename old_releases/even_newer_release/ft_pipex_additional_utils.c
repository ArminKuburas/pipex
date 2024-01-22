/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_additional_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:36:57 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/22 07:00:19 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	pipex_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return (0);
		}
		s++;
	}
	return (1);
}

int	waiting_function(t_handler *message, pid_t pid, char *command)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit_handler(3, message);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		ft_printf("pipex: exec format error: %s\n", command);
		return (1);
	}
	else
		return (0);
}
