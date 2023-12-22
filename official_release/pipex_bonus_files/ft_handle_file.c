/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:51:33 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/22 16:51:34 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	handle_file(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (in_or_out == 2)
		fd = open (file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		exit(0);
	return (fd);
}