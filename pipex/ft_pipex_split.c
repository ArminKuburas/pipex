/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:28:10 by akuburas          #+#    #+#             */
/*   Updated: 2023/12/18 14:59:11 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	start = *index;
	if (s[start] == '\'' || s[start] == '"')
	{
		quote = s[start];
		(*index)++;
		while (s[*index] && s[*index] != quote)
			(*index)++;
		end = ++(*index);
	}
	else
	{
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
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		result[j] = extract_word(s, &i);
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

int main(void)
{
	char command[] = "awk '{ut += $3} {ft+= $2} END {printf(\"%.2f\", ut/ft*100)}'";
	char **args = ft_pipex_split(command);

	if (args)
	{
		int i = 0;
		while (args[i])
		{
			printf("Token %d: %s\n", i, args[i]);
			i++;
		}
		if (args[i] == NULL)
			printf("The third token is set to NULL.\n");
		else
			printf("The third token is not set to NULL.\n");
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	return (0);
}