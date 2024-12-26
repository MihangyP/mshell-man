/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:07:32 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:55:59 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_fork_cmd(t_mshell *mshell, char **env, t_ast_node *ast)
{
	pid_t			pid;
	t_exec_status	status;

	status.status = 0;
	status.in_pipe = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		executor(env, ast, &status);
		free_ast(&ast);
		free_arr(env);
		exit(status.status);
	}
	else
		wait_child_process(mshell);
}

void	handle_built_in_cmd(t_ast_node *ast, char ***env, t_mshell *mshell)
{
	int		fd_in;
	int		fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (ast->redirection && check_redirection_exec(ast, *env, 0, 1) == 0)
	{
		mshell->exit_code = 1;
		my_close_fds(fd_in, fd_out);
		return ;
	}
	if (ft_strncmp(ast->args[0], "cd", 3) == 0)
		mshell->exit_code = cd_mshell(ast->args, env);
	else if (ft_strncmp(ast->args[0], "export", 7) == 0)
		mshell->exit_code = export_mshell(ast->args, env);
	else if (ft_strncmp(ast->args[0], "unset", 6) == 0)
		mshell->exit_code = unset_mshell(ast->args, env);
	else if (ft_strncmp(ast->args[0], "exit", 5) == 0)
	{
		my_close_fds(fd_in, fd_out);
		mshell->exit_code = exit_mshell(ast->args, ast, *env, 1);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	my_close_fds(fd_in, fd_out);
}

char	*find_path(char **path_list, char *cmd)
{
	if (cmd == 0)
		return (0);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (0);
	}
	return (check_path(path_list, cmd));
}

char	**find_path_list(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strnstr(env[i], "PATH", 4);
		if (tmp != 0)
			break ;
		i++;
	}
	if (tmp)
		return (ft_split(tmp + 5, ':'));
	else
		return (NULL);
}

char	**check_void_cmd(char **cmd, char **envp, t_ast_node *ast)
{
	char	**tmp;
	int		i;

	if (cmd == NULL)
		return (NULL);
	i = 0;
	tmp = cmd;
	while (ft_strlen(tmp[i]) == 0 && tmp[i] != NULL)
		i++;
	if (tmp[i] == NULL)
	{
		free_arr(envp);
		free_ast(&ast);
		exit(EXIT_SUCCESS);
	}
	tmp += i;
	return (tmp);
}
