/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:47:51 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/14 17:02:58 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(void)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	buffer[1000];
	ssize_t	bytes_read;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[1]);
		bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
		if (bytes_read == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		buffer[bytes_read] = '\0';
		printf("Child process recieved: %s\n", buffer);
		close(pipe_fd[0]);
	}
	else
	{
		close(pipe_fd[0]);
		const char *message = "Hello from the parent!";
		ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));

		if (bytes_written == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
		wait(NULL);
	}
	return (0);
}
