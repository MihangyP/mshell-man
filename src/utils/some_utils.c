/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:33:58 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 17:14:09 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_invalid_redirection(t_token *token)
{
	return (token == NULL || token->type != TOKEN_WORD);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
}

int	my_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	check_eof(char *str)
{
	if (*str == '\0')
	{
		free(str);
		return (1);
	}
	return (0);
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}
