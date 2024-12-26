/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:54:36 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:40:43 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	executor(char **env, t_ast_node *ast, t_exec_status *status)
{
	if (ast->type == 0)
		exec_cmd(env, ast, status);
	else if (ast->type == 1)
		pipe_cmd(env, ast, status);
}

void	execute(t_ast_node *ast, char **env, char **cmd, int *flag)
{
	char			**path_list;
	char			*path;

	(void)ast;
	path_list = find_path_list(env);
	path = find_path(path_list, cmd[0]);
	if (path_list)
		free_arr(path_list);
	if (path == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		if (ft_strchr(cmd[0], '/') == 0)
			ft_putstr_fd(" : command not found\n", 2);
		else
			ft_putstr_fd(" : No such file or directory\n", 2);
		*flag = 127;
		return ;
	}
	if (execve(path, cmd, env) == -1)
	{
		if (check_directory_error(path, cmd[0]) == 0)
			perror(cmd[0]);
		*flag = 126;
		return ;
	}
}

int	check_n_exec_built_in(char **cmd, char **env, t_ast_node *ast, int *flag)
{
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		pwd_mshell(cmd, env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		echo_mshell(cmd);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		*flag = exit_mshell(cmd, ast, env, 0);
		return (1);
	}
	return (0);
}

int	check_n_exec_built_in1(char **cmd, char **env, int *flag)
{
	if (ft_strncmp(cmd[0], "export", 7) == 0)
	{
		export_mshell(cmd, &env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		cd_mshell(cmd, &env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
	{
		unset_mshell(cmd, &env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
	{
		env_mshell(env, cmd);
		*flag = 0;
		return (1);
	}
	return (0);
}

void	handle_ast(t_mshell *mshell)
{
	if (mshell->ast->type == AST_COMMAND && mshell->ast->args != NULL
		&& check_built_in(mshell->ast) == 1)
		handle_built_in_cmd(mshell->ast, &mshell->env, mshell);
	else
		execute_fork_cmd(mshell, mshell->env, mshell->ast);
}
