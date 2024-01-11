/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:28:10 by akuburas          #+#    #+#             */
/*   Updated: 2024/01/10 14:25:55 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	inside_quotes(char c, char *quote)
{
	static char	save;

	if ((c == '\'' || c == '"') && (*quote == 0))
	{
		save = c;
		*quote = 1;
		return (1);
	}
	else if ((c == '\'' || c == '"') && save == c)
	{
		save = 0;
		*quote = 0;
		return (0);
	}
	return (0);
}

static int	count_words(const char *s)
{
	int		count;
	int		in_word;
	char	quote;

	count = 0;
	in_word = 0;
	quote = 0;
	while (*s)
	{
		if (*s == ' ' && !quote)
			in_word = 0;
		else if (inside_quotes(*s, &quote))
		{
			in_word = 1;
			count++;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*extract_word(const char *s, int *index)
{
	int		start;
	int		end;
	char	quote;

	while (s[*index] == ' ')
		(*index)++;
	if (s[*index] == '\'' || s[*index] == '"')
	{
		quote = s[*index];
		(*index)++;
		start = *index;
		while (s[*index] && s[*index] != quote)
			(*index)++;
		end = (*index);
	}
	else
	{
		start = *index;
		while (s[*index] && s[*index] != ' ')
			(*index)++;
		end = *index;
	}
	return (ft_strndup(s + start, end - start));
}

char	**ft_pipex_split(const char *s)
{
	char	**result;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	count = count_words(s);
	ft_printf("count is %d\n", count);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		result[j] = extract_word(s, &i);
		ft_printf("lets see the result: %s\n", result[j]);
		if (!result[j])
		{
			ft_free_substrings(result);
			return (NULL);
		}
		j++;
	}
	result[count] = NULL;
	return (result);
}
