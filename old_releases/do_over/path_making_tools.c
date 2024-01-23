/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_making_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:00:45 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/18 16:58:22 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char *find_path(char *str, env)
{
	
}

void	path_maker(t_pipex *info, int i, char **argv, char **env)
{
	int	j;

	j = i + 2;
	info->commands[i] = pipex_split(argv[j]);
	info->access_type = access_check(info->commands[i][0]);
	if (info->access_type == 2)
		info->path[i] = ft_strdup(info->commands[i][0]);
	else if (info->access_type == 1)
		path_error(info->commands[i][0], 1);
	else if (info->access_type == 0)
	{
		info->path[i] = find_path(info->commands[i][0], env);
		if (!(info->path[i]))
		
	}
}
