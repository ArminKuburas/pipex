/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:44:37 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/20 15:14:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(s);
	new_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (new_str)
	{
		ft_memcpy(new_str, s, n);
	}
	return (new_str);
}
