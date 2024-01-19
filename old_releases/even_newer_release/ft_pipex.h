/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:24:21 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/20 01:07:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

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
char	**ft_pipex_split(const char *s, t_handler *message);
void	ft_free_substrings(char **arr_str);
int		open_file(char *file, int in_or_out);
char	*ft_path_make(char *terminal_function, char **env);
void	exit_handler(int type, t_handler *message);
void	path_maker(char **env, t_handler *message, char *command, int type);
void	in_error_handler(int p_fd[]);
void	message_handler(char **argv, char **env, t_handler *message);
void	path_error_handler(char *function, t_handler *message, int type);
void	ft_freeing_message(t_handler *message);
void	handle_access(char *function, t_handler *message);
int		pipex_strchr(const char *s, int c);

#endif