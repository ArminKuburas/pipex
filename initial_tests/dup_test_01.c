/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_test_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:41:14 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/14 16:13:39 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	file_fd;
	int	original_stdout;

	file_fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	original_stdout = dup(fileno(stdout));
	if (dup2(file_fd, fileno(stdout)) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	printf("This goes to the file.\n");
	if (dup2(original_stdout, fileno(stdout)) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	printf("This goes back to the original stdout.\n");
	close(file_fd);
	return (0);
}
