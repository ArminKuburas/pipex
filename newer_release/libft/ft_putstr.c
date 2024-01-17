/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:25:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/17 10:27:51 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *string)
{
	int	i;
	int	result;

	result = 0;
	if (string == NULL)
	{
		write (2, "(null)", 6);
		return (6);
	}
	i = 0;
	while (string[i])
	{
		result = ft_putchar(string[i]);
		if (result == -1)
			return (-1);
		i++;
	}
	return (i);
}
