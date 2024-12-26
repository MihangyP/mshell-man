/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:04:42 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 14:04:45 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd_mshell(char **args, char **env)
{
	char	*pwd;

	(void)args;
	(void)env;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	if (pwd)
		free(pwd);
	return (EXIT_SUCCESS);
}
