/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:40:13 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:11:25 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_len_word(char *input, int *index)
{
	int		start;
	int		end;
	int		in_quotes;
	char	type_quotes;

	in_quotes = 0;
	type_quotes = 0;
	start = *index;
	end = start;
	while (input[end] != '\0')
	{
		if (!in_quotes && is_special_char(input[end]) == 1)
			break ;
		if (input[end] == '\'' || input[end] == '"')
			block_if_for_get_len_word(input, end, &in_quotes, &type_quotes);
		end++;
	}
	return (end - start + 1);
}

int	get_fd(char *input, int *index)
{
	int	fd;

	fd = -1;
	if (ft_isdigit(input[*index]) && (input[*index + 1] == '>'
			|| input[*index + 1] == '<'))
	{
		fd = ft_atoi(input + *index);
		*index += 1;
	}
	return (fd);
}

void	block_if_for_lexer(t_token **current, t_token **head,
								t_token *new_token)
{
	if (*head == NULL)
	{
		*head = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
}

void	block_if_for_get_len_word(char *input, int index,
										int *in_quotes, char *type_quotes)
{
	if (!*in_quotes)
	{
		*in_quotes = 1;
		*type_quotes = input[index];
	}
	else if (input[index] == *type_quotes)
	{
		*in_quotes = 0;
		*type_quotes = 0;
	}
}

t_token	*add_new_token(t_token *expanded_tokens, t_token *new_token,
	t_token **last)
{
	if (expanded_tokens == NULL)
		expanded_tokens = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
	return (expanded_tokens);
}
