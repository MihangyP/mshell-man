/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:35:30 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:13:27 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		printf("%s\n", curr->value);
		curr = curr->next;
	}
}

void	process_line(t_mshell *mshell)
{
	t_token		*expanded;

	mshell->token = lexer(mshell->entry);
	if (mshell->token == NULL)
	{
		mshell->ast = NULL;
		return ;
	}
	if (analyze_tokens(mshell->token) == 0)
	{
		close_tmp();
		free_token(mshell->token);
		mshell->exit_code = 2;
		return ;
	}
	expanded = expand_tokens(mshell->token, mshell->env, mshell->exit_code);
	free_token(mshell->token);
	mshell->ast = parse(expanded);
	free_token(expanded);
	if (mshell->ast->type == AST_COMMAND && mshell->ast->args != NULL
		&& mshell->ast->args[0] == NULL)
		return ;
	handle_ast(mshell);
}

int	start_mshell(t_mshell *mshell)
{
	int	state;

	uptdate_history(mshell);
	if (!(*mshell->entry) || is_empty(mshell->entry))
		return (0);
	state = heredoc(mshell, mshell->exit_code);
	if (handle_state(state) == 1)
		return (1);
	else if (handle_state(state) == 2)
		return (2);
	if (check_eof(mshell->entry) == 1)
		return (1);
	if (get() == 130)
		mshell->exit_code = 130;
	process_line(mshell);
	return (0);
}
