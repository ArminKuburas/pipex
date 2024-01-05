/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:09:15 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 18:08:13 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

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

static void	exit_path(char *function, int type)
{
	if (type == 2)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(function, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	if (type == 1)
	{
		ft_putstr_fd(function, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
}
typedef struct s_handler
{
	int		amount;
	int		fd_in;
	int		fd_out;
	int		in_error;
	int		out_error;
	int		signal_value;
	char	*path[2];
	int		values[2];
}					t_handler;


char	*ft_path_make(t_handler *message, char **argv, char **env, int argc)
{
	int	amount;

	amount = argc - 2;
	access_value_check()
	if (access_value == 0)
		return (terminal_function);
	if (access_value == 2)
		exit_path(terminal_function, 2);
	path_str = get_path("PATH", env);
	if (!path_str)
		exit_path(terminal_function, 1);
	all_paths = ft_split(path_str, ':');
	function_path = function_path_maker(terminal_function, all_paths);
	if (function_path == NULL)
		return (NULL);
	return (function_path);
}
