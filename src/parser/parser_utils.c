/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:43:48 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 22:08:35 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	count_type_token(t_token *tokens, int *count)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL && tmp->type != PIPE
		&& tmp->type != M_EOF)
	{
		if (tmp->type == ARG)
			count[ARG_COUNT] += 1;
		if (tmp->type == REDIRECT_IN_OUT)
		{
			tmp = tmp->next;
			if (tmp->type == ARG)
				count[REDIR_COUNT] += 1;
		}
		count_redir(&tmp, count);
		tmp = tmp->next;
	}
}

void	init_args_input_output_file(t_ast_node **cmd, int *count)
{
	if (count[ARG_COUNT] != 0)
		(*cmd)->args = (char **)ft_calloc(count[ARG_COUNT] + 1,
				sizeof(char *));
	if (count[REDIR_COUNT] != 0)
		(*cmd)->redirection = (t_redir *)ft_calloc(count[REDIR_COUNT] + 1,
				sizeof(t_redir));
}

void	process_token(t_token **tokens, t_ast_node *cmd, int *count,
	int *counts)
{
	if ((*tokens)->type == ARG && count[ARG_COUNT] != 0)
	{
		if ((*tokens)->value != NULL)
			cmd->args[counts[ARG_COUNT]++] = ft_strdup((*tokens)->value);
		else
			cmd->args[counts[ARG_COUNT]++] = NULL;
	}
	if ((*tokens)->type == REDIRECT_IN)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
	if ((*tokens)->type == REDIRECT_OUT)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
	if ((*tokens)->type == REDIRECT_APPEND)
		handle_redirection(tokens, cmd->redirection,
			&counts[REDIR_COUNT], count[REDIR_COUNT]);
	if ((*tokens)->type == HEREDOC)
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
