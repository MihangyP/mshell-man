/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:21:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 10:27:44 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_heredoc(char **line, int fd)
{
	*line = readline("> ");
	if (*line == NULL)
	{
		if (g_signal)
		{
			close(fd);
			return (-1);
		}
		close(fd);
		return (-2);
	}
	return (1);
}

int	process_heredoc_redir(t_utils_heredoc utils_var, char **env,
	int exit_code)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	while (1 && utils_var.fd > 0)
	{
		if (init_heredoc(&line, utils_var.fd) < 0)
		{
			if (g_signal == SIGINT)
				return (130);
			return (166);
		}
		result = get_result(line, utils_var.is_expand, env, exit_code);
		if (check_delimiter(utils_var.tmp_value, result, line))
			break ;
		ft_putendl_fd(result, utils_var.fd);
		free(line);
		free(result);
	}
	close(utils_var.fd);
	return (1);
}

char	*get_name_file(int in_pipe)
{
	char	*nb;
	char	*name;

	nb = NULL;
	nb = ft_itoa(in_pipe);
	name = ft_strjoin(".tmp", nb);
	free(nb);
	return (name);
}

int	handle_state(int state)
{
	if (state == 130)
	{
		close_tmp();
		return (1);
	}
	else if (state == 166)
	{
		close_tmp();
		return (2);
	}
	return (0);
}

void	close_tmp(void)
{
	char	*name;
	char	*nb;
	int		i;

	i = 0;
	while (1)
	{
		nb = ft_itoa(i);
		name = ft_strjoin(".tmp", nb);
		if (unlink(name) == -1)
		{
			free(nb);
			free(name);
			break ;
		}
		free(nb);
		free(name);
		i++;
	}
}
