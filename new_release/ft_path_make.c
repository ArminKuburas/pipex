/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:09:15 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 12:09:32 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

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

char	*ft_path_make(char *terminal_function, char **env)
{
	char	**all_paths;
	char	*function_path;
	char	*path_str;
	int		access_value;

	access_value = access_checker(terminal_function);
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
