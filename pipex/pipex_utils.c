/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:28 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/18 15:07:14 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
ft_path_make(char *terminal_function,char **env)
{
	
}