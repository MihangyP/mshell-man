/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:31:42 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:33:19 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_built_in(t_ast_node *ast)
{
	if (ft_strncmp(ast->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(ast->args[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(ast->args[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(ast->args[0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	count_redirection(t_token **tokens, int *count)
{
	if ((*tokens)->type == TOKEN_REDIR_IN)
	{
		*tokens = (*tokens)->next;
		if ((*tokens)->type == TOKEN_WORD)
			count[REDIR_COUNT] += 1;
	}
	if ((*tokens)->type == TOKEN_REDIR_OUT)
	{
		*tokens = (*tokens)->next;
		if ((*tokens)->type == TOKEN_WORD)
			count[REDIR_COUNT] += 1;
	}
	if ((*tokens)->type == TOKEN_REDIR_APPEND)
	{
		*tokens = (*tokens)->next;
		if ((*tokens)->type == TOKEN_WORD)
			count[REDIR_COUNT] += 1;
	}
	if ((*tokens)->type == TOKEN_HEREDOC)
	{
		*tokens = (*tokens)->next;
		if ((*tokens)->type == TOKEN_WORD)
			count[REDIR_COUNT] += 1;
	}
}

int	is_redirection(t_tokentype type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN_OUT)
		return (1);
	return (0);
}

int	process_tokens_heredoc(t_token *token, t_mshell *mshell, int exit_code)
{
	static int	in_pipe;
	int			status;
	t_token		*tmp_token;

	in_pipe = 0;
	status = 0;
	tmp_token = token;
	while (tmp_token)
	{
		if (tmp_token->type == TOKEN_PIPE)
			in_pipe += 1;
		if (tmp_token->type == TOKEN_HEREDOC)
			status = process_heredoc_token(&tmp_token, mshell, exit_code,
					in_pipe);
		if (status == -2)
			break ;
		tmp_token = tmp_token->next;
	}
	return (status);
}

char	*get_result(char *line, int is_expand, char **env, int exit_code)
{
	char	*result;

	result = NULL;
	if (line != NULL && is_expand == 0)
		result = special_expand_char(line, env, exit_code);
	else
		result = ft_strdup(line);
	return (result);
}
