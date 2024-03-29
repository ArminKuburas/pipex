/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:24:21 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/10 12:44:38 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_handler
{
	int		fd_in;
	int		fd_out;
	int		in_error;
	int		out_error;
	int		path_error;
	char	*path[2];
	pid_t	pid_one;
	pid_t	pid_two;
	char	**function_commands_one;
	char	**function_commands_two;
}					t_handler;
char	**ft_pipex_split(const char *s);
void	ft_free_substrings(char **arr_str);
int		open_file(char *file, int in_or_out);
char	*ft_path_make(char *terminal_function, char **env);
void	exit_handler(int type);
void	function_path_maker(char **argv, char **env, t_handler *message);
void	in_error_handler(int p_fd[]);
void	message_handler(char **argv, char **env, t_handler *message);
void	path_error_handler(char *function, t_handler *message, int type);

#endif