/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:50:09 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/12 11:54:07 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main()
{
	const	char 	*program_path = "/bin/ls";
	char *const		argv[] = { "ls", "-l", NULL };
	char *const envp[] = { NULL };
	
	if (execve(program_path, argv, envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	printf("This won't be reached!\n");
	return (0);
}