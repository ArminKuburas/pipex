/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_test_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:29:03 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/11 14:03:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)	
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		printf("I am the child process (PID: %d)\n", getpid());
	else
		printf("I am the parent process (Child PID: %d)\n", pid);
	return (0);
}
