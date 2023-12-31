/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:23:32 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/02 13:23:29 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line_bonus.h"

void	exit_handler(int n_exit);
int		handle_file(char *file, int in_or_out);
void	here_doc_handler(char **argv, int argc, int *fd_out);

#endif