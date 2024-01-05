/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:12:57 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/03 14:56:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

int	file_opener( char *file, int type)
{
	int	fd;

	if (type == 0)
	{
		fd = open(file, O_RDONLY, 0777);
		ft_putstr_fd("trying to open file1", 2);
	}
	else if (type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (type == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = -1;
	if (fd == -1)
	{
		ft_putstr_fd("doing exit 0", 2);
		exit(0);
	}
	return (fd);
}

void	exit_handler(int value)
{
	if (value == 1)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	if (value == 2)
	{
		ft_putstr_fd(" ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		exit(1);
	}
}
