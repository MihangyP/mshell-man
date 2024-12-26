/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:37:33 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 21:54:58 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		if (my_is_space(input[i]))
		{
			i++;
			continue ;
		}
		new_token = get_next_token(input, &i);
		if (new_token == NULL)
			break ;
		block_if_for_lexer(&current, &head, new_token);
	}
	if (current == NULL)
		return (NULL);
	current->next = create_token(M_EOF, "\0", &i, -1);
	return (head);
}

t_token	*get_next_token(char *input, int *index)
{
	int	fd;

	fd = get_fd(input, index);
	if (input[*index] == '|')
		return (create_token(PIPE, "|", index, fd));
	else if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
			return (create_token(REDIRECT_APPEND, ">>", index, fd));
		return (create_token(REDIRECT_OUT, ">", index, fd));
	}
	else if (input[*index] == '<')
	{
		if (input[*index + 1] == '>')
			return (create_token(REDIRECT_IN_OUT, ">", index, fd));
		if (input[*index + 1] == '<')
			return (create_token(HEREDOC, "<<", index, fd));
		return (create_token(REDIRECT_IN, "<", index, fd));
	}
	else if (input[*index] == '\n')
		return (create_token(M_NEWLINE, "\n", index, fd));
	else if (input[*index] == '\0')
		return (create_token(M_EOF, "\0", index, fd));
	else
		return (get_token_word(input, index));
}

t_token	*create_token(t_token_opt type, const char *value, int *index,
	int fd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (fd == 1 || fd == 2 || fd == 0)
		token->fd = fd;
	else
		token->fd = 0;
	token->next = NULL;
	if (index != NULL)
		*index += ft_strlen(value);
	return (token);
}

t_token	*get_token_word(char *input, int *index)
{
	t_token	*token;
	char	*word;
	int		len;

	len = get_len_word(input, index);
	word = malloc(sizeof(char) * len);
	ft_strlcpy(word, input + *index, len);
	if (word == NULL)
		return (NULL);
	token = create_token(ARG, word, index, -1);
	free(word);
	return (token);
}
