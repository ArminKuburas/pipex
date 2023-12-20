/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:03:05 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/20 10:54:51 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

char	*ft_strndup(const char *s, size_t n);
void	ft_free_substrings(char **arr_str);
char	**ft_pipex_split(const char *s);
char	*ft_path_make(char *terminal_function, char **env);
int		ft_strcmp(char *s1, char *s2);

#endif