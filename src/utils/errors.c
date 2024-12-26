/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:24:10 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 21:54:36 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_directory_error(char *path, char *cmd)
{
	struct stat		stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" : Is a directory", 2);
		return (1);
	}
	return (0);
}

int	check_pipe(t_token *current_token, int arg_count)
{
	if (current_token->next == NULL || arg_count == 0
		|| current_token->next->type == M_EOF)
	{
		ft_putstr_fd("Syntax error: expected command after pipe.\n", 2);
		return (0);
	}
	return (1);
}

int	print_syntax_error(void)
{
	ft_putstr_fd("Syntax error: expected filename after redirection"
		" or expected delimiter after heredoc\n", 2);
	return (0);
}

int	check_redirection(t_token **current_token)
{
	*current_token = (*current_token)->next;
	if (is_invalid_redirection(*current_token))
		return (print_syntax_error());
	return (1);
}
