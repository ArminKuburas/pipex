/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 12:09:10 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_free_substrings(char **arr_str)
{
	int	i;

	i = 0;
	while (arr_str[i])
	{
		free(arr_str[i]);
		arr_str[i] = NULL;
		i++;
	}
	free(arr_str);
	arr_str = NULL;
}

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
		if (path == NULL)
			exit(-1);
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

static char	*function_path_maker(char *terminal_function, char **all_paths)
{
	int		i;
	char	*test_path;
	char	*function_path;

	i = 0;
	while (all_paths[i])
	{
		test_path = ft_strjoin(all_paths[i], "/");
		if (!test_path)
			return (NULL);
		function_path = ft_strjoin(test_path, terminal_function);
		free(test_path);
		if (!function_path)
			return (NULL);
		if (access(function_path, F_OK | X_OK) == 0)
			return (function_path);
		free (function_path);
		i++;
	}
	return (NULL);
}

static int	access_checker(char *function)
{
	if (access(function, F_OK) == 0)
	{
		if (access(function, X_OK) == 0)
			return (0);
		return (2);
	}
	return (1);
}


