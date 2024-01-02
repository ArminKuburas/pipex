/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:44:41 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/02 12:43:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "pipex.h"

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

static void	pipe_child_maker(char *command, char **env, pid_t *pid)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	(*pid) = fork();
	if ((*pid) == -1)
		exit(0);
	if (!(*pid))
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ft_execute(command, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;
	pid_t	pid[12288];
	int		i;

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
	i = 0;
	while (i < argc -2)
		pipe_child_maker(argc, argv[i++], env, pid[i++]);
	dup2(fd_out, 1);
	ft_execute(argv[argc - 2], env);
	return (0);
}
