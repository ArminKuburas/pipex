/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:36:04 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/14 17:02:37 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[], char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		printf("%s\n", env[i++]);
	return (0); 
}
