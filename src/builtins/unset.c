/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:04:49 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:04:52 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	lst_srch_var(t_list *lst, char *var_name)
{
	char	*tmp;

	while (lst)
	{
		tmp = get_var_name((char *)lst->content);
		if (my_strcmp(tmp, var_name) == 0)
		{
			free (tmp);
			return (1);
		}
		free (tmp);
		lst = lst->next;
	}
	return (0);
}

void	remove_one(t_list **env_lst, char *to_remove)
{
	t_list	*tmp;
	char	*content;

	tmp = *env_lst;
	if (tmp == NULL || to_remove == NULL)
		return ;
	content = get_var_name((char *)tmp->content);
	if (my_strcmp(to_remove, content) == 0)
	{
		*env_lst = tmp->next;
		free(content);
		free(tmp->content);
		free(tmp);
	}
	else
	{
		free (content);
		remove_one(&tmp->next, to_remove);
	}
}

int	unset_mshell(char **cmd, char ***env)
{
	t_list	*env_lst;
	int		i;

	i = 1;
	env_lst = get_env_lst(*env);
	while (cmd[i])
	{
		remove_one(&env_lst, cmd[i]);
		i++;
	}
	free_arr(*env);
	*env = list_to_tab(env_lst);
	free_env_lst(env_lst);
	return (EXIT_SUCCESS);
}
