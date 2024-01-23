/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/18 16:13:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"

typedef struct s_pipex
{
	int		*error;
	int		amount;
	int		access_type;
	char	**path;
	char	***commands;
	int		fds[2];
}				t_pipex;

int	access_check(char *str);

#endif