/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:50:22 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/02 15:43:31 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (i[s1] || i[s2])
	{
		if (i[s1] != i[s2])
			return (i[s1] - i[s2]);
		i++;
	}
	return (0);
}
