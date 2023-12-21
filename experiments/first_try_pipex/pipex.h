/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:03:05 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/20 13:25:50 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>
# include "../libft/libft.h"

char	*ft_strndup(const char *s, size_t n);
void	ft_free_substrings(char **arr_str);
char	**ft_pipex_split(const char *s);
char	*ft_path_make(char *terminal_function, char **env);
int		ft_strcmp(char *s1, char *s2);
int		open_file(char *file, int in_or_out);

#endif