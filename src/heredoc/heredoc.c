/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:54:25 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:08:43 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal = 0;

int	heredoc(t_mshell *mshell, int exit_code)
{
	pid_t	pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid_child == 0)
		handle_child_process(mshell, exit_code);
	else
		return (wait_process(mshell));
	return (0);
}

void	handle_child_process(t_mshell *mshell, int exit_code)
{
	struct sigaction	sa;
	t_token				*token;
	int					status;

	g_signal = 0;
	setup_signals_heredoc(&sa);
	status = 1;
	token = lexer(mshell->entry);
	if (token == NULL)
		exit(status);
	status = process_tokens_heredoc(token, mshell, exit_code);
	free_token(token);
	free_arr(mshell->env);
	free(mshell->entry);
	exit(status);
}

int	wait_process(t_mshell *mshell)
{
	int	status;

	sigaction(SIGINT, &mshell->sa_ignore, NULL);
	wait(&status);
	sigaction(SIGINT, &mshell->sa, NULL);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (130);
		else
			return (WEXITSTATUS(status));
	}
	return (0);
}

int	here_doc(int in_pipe, t_ast_node *node, char **env, int flag)
{
	char	*nb;
	char	*name;
	int		fd;

	nb = ft_itoa(in_pipe);
	name = ft_strjoin(".tmp", nb);
	fd = open(name, O_RDONLY);
	free(name);
	free(nb);
	if (fd < 0)
	{
		perror ("heredoc");
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_arr(env);
		exit (EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (1);
}

t_token	*process_heredoc(t_token *current, t_token *expanded_tokens,
							t_token **last)
{
	t_token	*new_token;
	int		tmp;

	new_token = create_token(current->type, current->value, &tmp, -1);
	expanded_tokens = add_new_token(expanded_tokens, new_token, last);
	return (expanded_tokens);
}
