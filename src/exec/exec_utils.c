/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:57:02 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 22:02:40 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_redirection_exec(t_ast_node *ast, char **env, int in_pipe, int flag)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	while (ast->redirection[i].target)
	{
		if (status == 0)
			return (status);
		if (ast->redirection[i].type_redirection == IN)
			status = redir_input(ast->redirection[i].target, ast, env, flag);
		else if (ast->redirection[i].type_redirection == OUT)
			status = redir_output(ast->redirection[i].target, ast, env, flag);
		else if (ast->redirection[i].type_redirection == APPEND)
			status = output_append(ast->redirection[i].target, ast, env, flag);
		else if (ast->redirection[i].type_redirection == O_HEREDOC)
			status = here_doc(in_pipe, ast, env, flag);
		i++;
	}
	return (status);
}

void	exec_cmd(char **env, t_ast_node *ast, t_exec_status *status)
{
	char	**tmp;

	tmp = check_void_cmd(ast->args, env, ast);
	if (ast->redirection)
		check_redirection_exec(ast, env, status->in_pipe, 0);
	if (ast->args == NULL)
		return ;
	if (check_n_exec_built_in(tmp, env, ast, &status->status) == 1
		|| check_n_exec_built_in1(tmp, env, &status->status) == 1)
		return ;
	execute(ast, env, tmp, &status->status);
}

void	pipe_exec_left(int fd[2], t_ast_node *ast, char **env,
							t_exec_status *status)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	executor(env, ast->left, status);
}

int	pipe_exec_right( int fd[2], t_ast_node *ast, char **env,
						t_exec_status *status)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	executor(env, ast->right, status);
	return (status->status);
}

void	pipe_cmd(char **env, t_ast_node *ast, t_exec_status *status)
{
	int			fd[2];
	pid_t		pid;
	pid_t		pid1;

	pid1 = 0;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		pipe_exec_left(fd, ast, env, status);
	else
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			status->in_pipe += 1;
			pipe_exec_right(fd, ast, env, status);
		}
	}
	wait_pipe_cmd(fd, status, pid, pid1);
}
