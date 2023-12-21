/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:44:41 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/21 20:56:02 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (argc < 5)
		exit_handler(1);
	i = 3;
	if (ft_strcmp(argv[1], "here_doc"))
		here_doc_handler(argv, argc, &fd_out);
	else
	{
		i = 2;
		fd_in = handle_file(argv[1], 0);
		fd_out = handle_file(argv[argc - 1], 1);
		dup(fd_in, 0);
	}
	while (i <= argc -2)
		pipe_child_maker(argc, argv[i++], env);
	return (0);
}
