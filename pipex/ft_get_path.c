/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:20:05 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/19 11:32:15 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *terminal_function, char **env)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		path = ft_substr(env[i], 0, j);
		if (ft_strcmp(path, terminal_function) == 0)
		{
			free(path);
			return (env[i] + j + 1);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_path_make(char *terminal_function, char **env)
{
	char	**all_paths;
	int		i;
	char	*test_path;
	char	*function_path;

	i = 0;
	all_paths = ft_split(get_path(terminal_function, env), ':');
	while (all_paths[i])
	{
		test_path = strjoin(all_paths[i], "/");
		function_path = strjoin(test_path, terminal_function);
		free(test_path);
		if (access(function_path, F_OK | X_OK) == 0)
			return (function_path);
		free (function_path);
	}
	return (NULL);
}
