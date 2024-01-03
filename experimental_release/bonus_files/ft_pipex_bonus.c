/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:12:50 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/03 13:18:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

static void	ft_execute(char *function, char **env)
{
	char	**function_commands;
	char	*path;

	function_commands = ft_pipex_split(function);
	path = ft_path_make(function_commands[0], env);
	if (execve(path, function_commands, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(function_commands[0], 2);
		ft_free_substrings(function_commands);
		free(path);
		exit(0);
	}
}

static void	child_pipe_maker(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ft_execute(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

int	main(int argc, char *argv[], char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	if (argc < 5)
		exit_handler(1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			exit_handler(2);
		i = 3;
		fd_out = file_opener(argv[argc - 1], 2);
		here_doc(argv);
	}
	else
	{
		i = 2;
		fd_in = file_opener(argv[1], 0);
		fd_out = file_opener(argv[argc - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < argc - 2)
		child_pipe_maker(argv[i++], env);
	dup2(fd_out, 1);
	ft_execute(argv[argc -2], env);
}
