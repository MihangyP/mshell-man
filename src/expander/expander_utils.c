/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:32:30 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:55:21 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_for_heredoc(char *heredoc_delimiter)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (heredoc_delimiter[i] != '\0')
	{
		if (heredoc_delimiter[i] == '\'' || heredoc_delimiter[i] == '"')
			i++;
		else if (heredoc_delimiter[i] == '$' && (heredoc_delimiter[i + 1]
				== '\'' || heredoc_delimiter[i + 1] == '"'))
			i++;
		else
		{
			result = char_append(result, heredoc_delimiter[i]);
			i++;
		}
	}
	if (result == NULL)
		return (ft_strdup(""));
	return (result);
}

int	process_heredoc_token(t_token **current, t_mshell *mshell, int exit_code,
	int in_pipe)
{
	char			*name;
	int				status;
	t_utils_heredoc	utils_heredoc;

	name = NULL;
	utils_heredoc.tmp_value = NULL;
	*current = (*current)->next;
	if (is_invalid_redirection(*current))
		return (-2);
	utils_heredoc.tmp_value = expand_for_heredoc((*current)->value);
	utils_heredoc.is_expand = determine_expansion(*current,
			utils_heredoc.tmp_value);
	name = get_name_file(in_pipe);
	utils_heredoc.fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	status = process_heredoc_redir(utils_heredoc, mshell->env, exit_code);
	free(name);
	free(utils_heredoc.tmp_value);
	return (status);
}

int	determine_expansion(t_token *current_token, char *tmp)
{
	if (my_strcmp(current_token->value, tmp) == 0)
		return (0);
	return (1);
}

void	init_expand_vars(t_expand_result *result, int *i)
{
	*i = -1;
	result->value = NULL;
	result->create_token = 0;
	result->prev = 0;
}

void	init_expand_context(t_expand_context *ctx,
			t_expand_result *result, int exit_code)
{
	ctx->result = result;
	ctx->exit_code = exit_code;
	ctx->in_single_quotes = 0;
	ctx->in_double_quotes = 0;
}
