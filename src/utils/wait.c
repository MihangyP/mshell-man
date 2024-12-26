/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:13:26 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 17:12:22 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_pipe_cmd(int fd[2], t_exec_status *status, int pid, int pid1)
{
	close(fd[1]);
	close(fd[0]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, NULL, 0);
	waitpid(pid1, &(status->status), 0);
	if (WIFEXITED(status->status))
		status->status = WEXITSTATUS(status->status);
}

void	wait_child_process(t_mshell *mshell)
{
	int	status;

	sigaction(SIGINT, &mshell->sa_ignore, NULL);
	wait(&status);
	sigaction(SIGINT, &mshell->sa, NULL);
	if (WIFEXITED(status))
		mshell->exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		mshell->exit_code = 128 + WTERMSIG(status);
	}
}
