/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:13:56 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 21:51:15 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*expand_tokens(t_token *tokens, char **env, int exit_code)
{
	t_token			*current;
	t_token			*last;
	int				skip_next;
	t_expand_params	params;

	current = tokens;
	last = NULL;
	skip_next = 0;
	init_expand_params(&params, env, exit_code, &last);
	while (current)
	{
		if (skip_next)
			skip_next = process_skip(current, &params, 0);
		else if (current->type == HEREDOC)
			skip_next = process_skip(current, &params, 1);
		else if (current->type == ARG)
			params.expanded_tokens = process_word(current, &params);
		else
			params.expanded_tokens = process_heredoc(current,
					params.expanded_tokens, params.last);
		current = current->next;
	}
	return (params.expanded_tokens);
}

void	init_expand_params(t_expand_params *params, char **env,
								int exit_code, t_token **last)
{
	params->env = env;
	params->exit_code = exit_code;
	params->expanded_tokens = NULL;
	params->last = last;
}

int	process_skip(t_token *current, t_expand_params *params, int flag)
{
	params->expanded_tokens = process_heredoc(current, params->expanded_tokens,
			params->last);
	if (flag == 1)
		return (1);
	return (0);
}

t_token	*split_word(char *word)
{
	char	*word_without_quotes;
	char	**split;
	int		i;
	t_token	*token;
	t_token	*last;

	token = NULL;
	last = NULL;
	i = 0;
	split = my_split(word, ' ');
	if (split[i] == NULL)
		return (free_arr(split), create_token(ARG, "", &i, -1));
	while (split[i] != NULL)
	{
		word_without_quotes = remove_quotes(split[i]);
		process_token_split(&token, &last,
			create_token(ARG, word_without_quotes, NULL, -1));
		free(word_without_quotes);
		i++;
	}
	free_arr(split);
	return (token);
}

t_token	*process_word(t_token *current, t_expand_params *params)
{
	char			*word_without_quotes;
	t_token			*new_token;
	int				tmp;
	t_expand_result	expanded;

	expanded.value = NULL;
	expanded = expand_token(current->value, params->env, params->exit_code);
	if (expanded.create_token == 1)
		new_token = split_word(expanded.value);
	else
	{
		word_without_quotes = remove_quotes(expanded.value);
		new_token = create_token(ARG, word_without_quotes, &tmp, -1);
		free(word_without_quotes);
	}
	params->expanded_tokens = add_new_token(params->expanded_tokens,
			new_token, params->last);
	while (new_token && new_token->next)
		new_token = new_token->next;
	*(params->last) = new_token;
	free(expanded.value);
	return (params->expanded_tokens);
}
