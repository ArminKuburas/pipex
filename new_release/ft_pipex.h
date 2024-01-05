/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:24:21 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/05 17:29:21 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_handler
{
	int		amount;
	int		fd_in;
	int		fd_out;
	int		in_error;
	int		out_error;
	int		signal_value;
	char	*path[2];
	int		values[2];
}					t_handler;
char	**ft_pipex_split(const char *s);
void	ft_free_substrings(char **arr_str);
int		open_file(char *file, int in_or_out);
char	*ft_path_make(char *terminal_function, char **env);

#endif