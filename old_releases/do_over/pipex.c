/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:55:49 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/18 16:11:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	info;

	if (argc < 5)
	{
		ft_printf("./pipex input cmd1 cmd2 output\n");
		return (1);
	}
	ft_bzero(&info, sizeof(t_pipex));
	set_up_info(&info, argc, argv, env);
}
