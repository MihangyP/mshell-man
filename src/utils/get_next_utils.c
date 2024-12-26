/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:41:11 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 09:52:41 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_line_break(char *str)
{
	int	i;

	if (NULL == str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	count_next_line_size(char *tmp)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (NULL == tmp)
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			count++;
			break ;
		}
		count++;
		i++;
	}
	return (count);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
