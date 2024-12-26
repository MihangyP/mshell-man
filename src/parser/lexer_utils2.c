/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:27:21 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 21:54:20 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	process_token_split(t_token **token, t_token **last, t_token *new_token)
{
	if (*token == NULL)
	{
		*token = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		*last = new_token;
	}
}

int	is_ignored_dollar(char current, char next, int in_double_quotes,
							int in_single_quotes)
{
	if (current == '$' && (next == '\'' || next == '"')
		&& (in_double_quotes || in_single_quotes))
		return (1);
	if (current == '$' && (next == '\'' || next == '"'))
		return (0);
	return (1);
}

char	*remove_quotes(char *str)
{
	int		in_d_quotes;
	int		in_s_quotes;
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	in_d_quotes = 0;
	in_s_quotes = 0;
	while (str[i] != '\0')
	{
		if (handle_quotes_expander(str[i], &in_s_quotes, &in_d_quotes))
		{
		}
		else
		{
			if (is_ignored_dollar(str[i], str[i + 1], in_d_quotes,
					in_s_quotes) == 1)
				result = char_append(result, str[i]);
		}
		i++;
	}
	return (result);
}

char	*finalize_result(char *result)
{
	if (result == NULL)
		return (ft_strdup(""));
	return (result);
}

int	analyze_tokens(t_token *tokens)
{
	t_token	*current;
	int		arg_count;

	current = tokens;
	arg_count = 0;
	while (current != NULL && current->type != M_EOF)
	{
		if (current->type == ARG)
			arg_count++;
		if (is_redirection(current->type))
		{
			if (check_redirection(&current) == 0)
				return (0);
			arg_count++;
		}
		if (current->type == PIPE)
		{
			if (check_pipe(current, arg_count) == 0)
				return (0);
			arg_count = 0;
		}
		current = current->next;
	}
	return (1);
}
