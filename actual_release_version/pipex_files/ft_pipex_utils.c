/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/02 17:45:48 by akuburas         ###   ########.fr       */
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

int	open_file(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	return (fd);
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

static void	exit_path(char *terminal_function)
{
	ft_putstr_fd(terminal_function, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(1);
}

char	*ft_path_make(char *terminal_function, char **env)
{
	char	**all_paths;
	int		i;
	char	*test_path;
	char	*function_path;
	char	*path_str;

	i = 0;
	path_str = get_path("PATH", env);
	if (!path_str)
		exit_path(terminal_function);
	all_paths = ft_split(path_str, ':');
	while (all_paths[i])
	{
		test_path = ft_strjoin(all_paths[i], "/");
		function_path = ft_strjoin(test_path, terminal_function);
		free(test_path);
		if (access(function_path, F_OK | X_OK) == 0)
			return (function_path);
		free (function_path);
		i++;
	}
	return (NULL);
}
