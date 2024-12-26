/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:43:48 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 11:47:39 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	count_type_token(t_token *tokens, int *count)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL && tmp->type != TOKEN_PIPE
		&& tmp->type != TOKEN_EOF)
	{
		if (tmp->type == TOKEN_WORD)
			count[ARG_COUNT] += 1;
		if (tmp->type == TOKEN_REDIR_IN_OUT)
		{
			tmp = tmp->next;
			if (tmp->type == TOKEN_WORD)
				count[REDIR_COUNT] += 1;
		}
		count_redirection(&tmp, count);
		tmp = tmp->next;
	}
}

void	init_args_input_output_file(t_ast_node **cmd, int *count)
{
	if (count[ARG_COUNT] != 0)
		(*cmd)->args = (char **)ft_calloc(count[ARG_COUNT] + 1,
				sizeof(char *));
	if (count[REDIR_COUNT] != 0)
		(*cmd)->redirection = (t_redirection *)ft_calloc(count[REDIR_COUNT] + 1,
				sizeof(t_redirection));
}

void	process_token(t_token **tokens, t_ast_node *cmd, int *count,
	int *counts)
{
	if ((*tokens)->type == TOKEN_WORD && count[ARG_COUNT] != 0)
	{
		if ((*tokens)->value != NULL)
			cmd->args[counts[ARG_COUNT]++] = ft_strdup((*tokens)->value);
		else
			cmd->args[counts[ARG_COUNT]++] = NULL;
	}
	if ((*tokens)->type == TOKEN_REDIR_IN)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
	if ((*tokens)->type == TOKEN_REDIR_OUT)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
	if ((*tokens)->type == TOKEN_REDIR_APPEND)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
	if ((*tokens)->type == TOKEN_HEREDOC)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
}

void	set_null_terminators(t_ast_node *cmd, int *count, int *counts)
{
	if (count[ARG_COUNT] != 0)
		cmd->args[counts[ARG_COUNT]] = NULL;
	if (count[REDIR_COUNT] != 0)
		cmd->redirection[counts[REDIR_COUNT]].target = NULL;
}
