/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:09:15 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/19 12:25:09 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static char	*get_path(char *path_name, char **env, t_handler *message)
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
			exit_handler(4, message);
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

void	handle_access(char *function, t_handler *message)
{
	if (access(function, F_OK) == 0)
	{
		printf("inside of handle access. printing the function %s\n", function);
		if (access(function, X_OK) == 0)
		{
			printf("inside of handle access. printing the function X_OK somehow passed.  %s\n", function);
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
			exit_handler(4, message);
		message->path[in_out] = ft_strjoin(test_path, funct);
		if (!(message->path[in_out]))
			exit_handler(4, message);
		free(test_path);
		ft_printf("Lets see what the path is inside of path helper %s", message->path[in_out]);
		handle_access(message->path[in_out], message);
		if (message->path_error == 2)
			return (1);
		free (message->path[in_out]);
		message->path[in_out] = NULL;
		if (message->path_error == 1 && in_out == 0)
			path_error_handler(funct, message, 1);
		if (message->path_error == 1 && in_out == 1)
			path_error_handler(funct, message, 2);
		i++;
	}
	return (0);
}

void	find_path(char *function, char **env, t_handler *message, int in_out)
{
	char	**all_paths;
	char	*path_str;
	int		helper_value;

	path_str = get_path("PATH", env, message);
	if (!path_str)
	{
		ft_printf("pipex: command not found: %s\n", function);
		if (in_out == 1)
			message->out_error = 127;
		else
			message->in_error = 1;
		return ;
	}
	all_paths = ft_split(path_str, ':');
	if (!all_paths)
		exit_handler(4, message);
	helper_value = path_helper(all_paths, message, in_out, function);
	ft_free_substrings(all_paths);
	if (helper_value == 1)
		return ;
	else if (helper_value == 2)
		return ;
	else if (helper_value == 0)
		message->path_error = 4;
}

void	path_maker(char **env, t_handler *message, char *command, int type)
{
	handle_access(command, message);
	if (message->path_error == 2)
	{
		ft_printf("inside of path maker. Inside of somehow ft_strdup of the command??\n");
		message->path[type] = ft_strdup(command);
		if (!(message->path[type]))
			exit_handler(4, message);
	}
	else if (message->path_error == 1)
	{
		if (type == 0 && message->in_error == 0)
			path_error_handler(command, message, 1);
		else if (type == 1 && message->out_error == 0)
			path_error_handler(command, message, 2);
		return ;
	}
	else if (message->path_error == 0)
		find_path(command, env, message, type);
	if (message->path_error == 4)
	{
		if (type == 0 && message->in_error == 0)
			path_error_handler(command, message, 3);
		else if (type == 1 && message->out_error == 0)
			path_error_handler(command, message, 4);
		return ;
	}
	ft_printf("Past the last if statement somehow\n");
}
