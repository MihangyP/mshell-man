/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:27:58 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:03:09 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	uptdate_history(t_mshell *mshell)
{
	char	*path;
	char	*tmp;

	add_history(mshell->entry);
	tmp = ft_strjoin(mshell->path, "/");
	path = ft_strjoin(tmp, ".history_file");
	mshell->hist_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (mshell->hist_fd != -1)
	{
		ft_putendl_fd(mshell->entry, mshell->hist_fd);
		close(mshell->hist_fd);
	}
	free(path);
	free(tmp);
}

void	get_history(int fd)
{
	char	*line;

	if (fd <= 0)
		return ;
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			line[ft_strlen(line) - 1] = '\0';
			add_history(line);
			free(line);
		}
		else
			break ;
	}
}
