/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:48:11 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:02:33 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	count_word_deep(const char *str, int *i, int *in_q, char *type_q)
{
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (*in_q && *type_q == str[*i])
			*in_q = 0;
		else if (!(*in_q))
		{
			*in_q = 1;
			*type_q = str[*i];
		}
	}
	(*i)++;
}

size_t	count_word(const char *str, char c)
{
	int			i;
	size_t		words;
	int			in_quotes;
	char		type_quote;

	i = 0;
	type_quote = 0;
	in_quotes = 0;
	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			words++;
			while (str[i] && (in_quotes || str[i] != c))
				count_word_deep(str, &i, &in_quotes, &type_quote);
		}
	}
	return (words);
}


size_t	len_word(const char *str, char c, size_t start)
{
	size_t	len;
	char	type_quote;
	int		in_quotes;

	len = 0;
	in_quotes = 0;
	while (str[start + len] && (in_quotes || str[start + len] != c))
	{
		if (str[start + len] == '\'' || str[start + len] == '"')
		{
			if (in_quotes && type_quote == str[start + len])
				in_quotes = 0;
			else if (!in_quotes)
			{
				in_quotes = 1;
				type_quote = str[start + len];
			}
		}
		len++;
	}
	return (len);
}

void	fc_split(const char *str, char c, char **split, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < words)
	{
		while (str[j] && str[j] == c)
			j++;
		split[i] = (char *)malloc(sizeof(char) * (len_word(str, c, j) + 1));
		while (k < len_word(str, c, j))
		{
			split[i][k] = str[j + k];
			k++;
		}
		split[i][k] = '\0';
		k = 0;
		j += len_word(str, c, j);
		i++;
	}
	split[i] = NULL;
}

char	**my_split(const char *str, char c)
{
	size_t	words;
	char	**split;

	if (str == NULL)
		return (NULL);
	words = count_word(str, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	fc_split(str, c, split, words);
	return (split);
}
