/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:58:37 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/21 06:28:31 by akuburas         ###   ########.fr       */
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
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
	{
		perror("right before exit inside of open_file");
		exit(0);
	}
	return (ret);
}

void	handle_exit(int exit_value)
{
	if (exit_value == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(0);
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