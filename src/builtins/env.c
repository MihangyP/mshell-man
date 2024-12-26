/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:04:10 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:04:12 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_mshell(char **env, char **cmd)
{
	int	i;

	if (cmd[1])
	{
		ft_putstr_fd("Error: usage : env\n", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i ++;
	}
	return (EXIT_SUCCESS);
}
