/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:09:15 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/09 09:36:48 by akuburas         ###   ########.fr       */
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
			exit(1);
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

static void	handle_access(char *function, t_handler *message)
{
	if (access(function, F_OK) == 0)
	{
		if (access(function, X_OK) == 0)
		{
			message->path_error = 2;
			return ;
		}
		message->path_error = 1;
		return ;
	}
	message->path_error = 0;
}

int	path_helper(char **all_paths, t_handler *message, int in_out, char *funct)
{
	char	*test_path;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		test_path = ft_strjoin(all_paths[i], "/");
		if (!test_path)
			exit (1);
		message->path[in_out] = ft_strjoin(test_path, funct);
		if (!(message->path[in_out]))
			exit(1);
		free(test_path);
		handle_access(message->path[in_out], message);
		if (message->path_error == 2)
			return (1);
		free (message->path[in_out]);
		if (message->path_error == 1 && in_out == 0)
			return (path_error_handler(funct, message, 1), 1);
		if (message->path_error == 1 && in_out == 1)
			path_error_handler(funct, message, 2);
		i++;
	}
	return (0);
}

void	find_path(char *function, char **env, t_handler *message, int in_out)
{
	char	**all_paths;
	int		i;
	char	*path_str;
	int		helper_value;

	i = 0;
	path_str = get_path("PATH", env);
	if (!path_str)
	{
		ft_printf("pipex: command not found: %s\n", function);
		return ;
	}
	all_paths = ft_split(path_str, ':');
	helper_value = path_helper(all_paths, message, in_out, function);
	if (helper_value == 1)
		return ;
	else if (helper_value == 0)
		message->path_error = 4;
}

void	function_path_maker(char **argv, char **env, t_handler *message)
{
	handle_access(argv[2], message);
	if (message->path_error == 1)
		path_error_handler(argv[2], message, 1);
	else if (message->path_error == 2)
		message->path[0] = argv[2];
	else
		find_path(argv[2], env, message, 0);
	if (message->path_error == 4)
		path_error_handler(argv[2], message, 3);
	handle_access(argv[3], message);
	if (message->path_error == 1)
		path_error_handler(argv[3], message, 2);
	else if (message->path_error == 2)
		message->path[1] = argv[3];
	else
		find_path(argv[3], env, message, 1);
	if (message->path_error == 4)
		path_error_handler(argv[2], message, 4);
}
