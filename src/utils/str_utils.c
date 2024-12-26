/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:57:24 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 17:14:01 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*str_append(char *str, char *append)
{
	char	*result;
	int		len1;
	int		len2;

	len1 = 0;
	if (str != NULL)
		len1 = ft_strlen(str);
	len2 = ft_strlen(append);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str)
		ft_strlcpy(result, str, (len1 + 1));
	ft_strlcpy(result + len1, append, len2 + 1);
	free(str);
	return (result);
}

int	is_delimiter(const char *line, const char *heredoc_delimiter)
{
	if (line == NULL)
		return (1);
	if (ft_strncmp(line, heredoc_delimiter,
			ft_strlen(heredoc_delimiter) + 1) == 0)
		return (1);
	return (0);
}

int	check_delimiter(char *heredoc_delimiter, char *result, char *line)
{
	if (is_delimiter(heredoc_delimiter, result))
	{
		free(line);
		if (result != NULL)
			free(result);
		return (1);
	}
	return (0);
}

int	my_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*char_append(char *str, char c)
{
	char	*result;
	int		len;

	len = 0;
	if (str != NULL)
		len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (len + 2));
	if (str)
		ft_strlcpy(result, str, (len + 1));
	result[len] = c;
	result[len + 1] = '\0';
	free(str);
	return (result);
}
