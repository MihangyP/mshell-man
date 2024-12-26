/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:30:08 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 12:40:23 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env_lst(t_list *env_lst)
{
	t_list	*tmp;

	while (env_lst)
	{
		tmp = env_lst;
		env_lst = env_lst->next;
		free(tmp->content);
		free(tmp);
	}
	free(env_lst);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
	token = NULL;
}

void	free_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	while (redirection[i].target != NULL)
	{
		free(redirection[i].target);
		i++;
	}
	free(redirection);
}

void	free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_ast(t_ast_node **node)
{
	if (node == NULL || *node == NULL)
		return ;
	if ((*node)->type != AST_PIPE && (*node)->args != NULL)
		free_arr((*node)->args);
	if ((*node)->type != AST_PIPE && (*node)->redirection != NULL)
		free_redirection((*node)->redirection);
	if ((*node)->left != NULL)
		free_ast(&(*node)->left);
	if ((*node)->right != NULL)
		free_ast(&(*node)->right);
	free(*node);
}
