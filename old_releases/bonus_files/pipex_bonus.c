#include "ft_pipex.h"

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



int	main(int argc, char *argv[], char **env)
{
	
}
