/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:09:15 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/16 17:52:54 by akuburas         ###   ########.fr       */
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
			exit_handler(4, message);
		message->path[in_out] = ft_strjoin(test_path, funct);
		if (!(message->path[in_out]))
			exit_handler(4, message);
		free(test_path);
		handle_access(message->path[in_out], message);
		if (message->path_error == 2)
			return (1);
		free (message->path[in_out]);
		if (message->path_error == 1 && in_out == 0)
			return (2);
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
	helper_value = path_helper(all_paths, message, in_out, function);
	if (helper_value == 1)
		return ;
	else if (helper_value == 2)
	{
		path_error_handler(function, message, 1);
		return ;
	}
	else if (helper_value == 0)
		message->path_error = 4;
}

void	function_path_maker(char **env, t_handler *message)
{
	handle_access(message->function_commands_one[0], message);
	if (message->path_error == 2 && message->in_error != 1)
		message->path[0] = ft_strdup(message->function_commands_one[0]);
	else if (message->path_error == 1)
		path_error_handler(message->function_commands_one[0], message, 1);
	else if ((message->path_error == 0 && message->in_error != 1))
		find_path(message->function_commands_one[0], env, message, 0);
	if (message->path_error == 4)
		path_error_handler(message->function_commands_one[0], message, 3);
	if (!(message->path[0]))
		exit_handler(4, message);
	handle_access(message->function_commands_two[0], message);
	if (message->path_error == 2 && message->out_error == 0)
		message->path[1] = ft_strdup(message->function_commands_two[0]);
	else if (message->path_error == 1)
		path_error_handler(message->function_commands_two[0], message, 2);
	else if (message->path_error != 2 && message->out_error == 0)
		find_path(message->function_commands_two[0], env, message, 1);
	if (message->path_error == 4)
		path_error_handler(message->function_commands_two[0], message, 4);
	if (!(message->path[1]))
		exit_handler(4, message);
}