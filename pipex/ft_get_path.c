/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:20:05 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/20 10:45:24 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char *path_name, char **env)
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
		if (ft_strcmp(path, path_name) == 0)
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
	all_paths = ft_split(get_path("PATH", env), ':');
	while (all_paths[i])
	{
		test_path = ft_strjoin(all_paths[i], "/");
		function_path = ft_strjoin(test_path, terminal_function);
		free(test_path);
		if (access(function_path, F_OK | X_OK) == 0)
			return (function_path);
		free (function_path);
	}
	return (NULL);
}
