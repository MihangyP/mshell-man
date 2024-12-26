/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:04:42 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 20:46:53 by irazafim         ###   ########.fr       */
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
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	if (pwd)
		free(pwd);
	return (EXIT_SUCCESS);
}
