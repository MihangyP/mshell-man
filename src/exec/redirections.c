/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:01:18 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:41:01 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_input(char *input, t_ast_node *node, char **env, int flag)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
	{
		perror (input);
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_arr(env);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	redir_output(char *output, t_ast_node *node, char **env, int flag)
{
	int	fd;

	fd = open(output, O_RDONLY | O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (fd < 0)
	{
		perror (output);
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_arr(env);
		exit (EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	output_append(char *out_append, t_ast_node *node, char **env, int flag)
{
	int	fd;

	fd = open(out_append, O_RDONLY | O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror (out_append);
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_arr(env);
		exit (EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}

char	*check_path(char **path_list, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	if (path_list == NULL)
		return (NULL);
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (access(path, F_OK) == 0)
		{
			free(tmp);
			return (path);
		}
		else
		{
			free(tmp);
			free(path);
			i++;
		}
	}
	return (0);
}

void	handle_redirection(t_token **tokens, t_redirection *redirection,
	int *file_count, int count)
{
	redirection[*file_count].fd = (*tokens)->fd;
	if ((*tokens)->type == TOKEN_REDIR_IN)
		redirection[*file_count].type_redirection = REDIRECTION_IN;
	if ((*tokens)->type == TOKEN_REDIR_OUT)
		redirection[*file_count].type_redirection = REDIRECTION_OUT;
	if ((*tokens)->type == TOKEN_REDIR_APPEND)
		redirection[*file_count].type_redirection = REDIRECTION_APPEND;
	if ((*tokens)->type == TOKEN_HEREDOC)
		redirection[*file_count].type_redirection = REDIRECTION_HEREDOC;
	*tokens = (*tokens)->next;
	if ((*tokens)->type == TOKEN_WORD && count != 0)
	{
		redirection[*file_count].target = ft_strdup((*tokens)->value);
		(*file_count)++;
	}
}
