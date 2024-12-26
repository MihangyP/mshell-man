/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:42:26 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/26 10:44:21 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_value(int value)
{
	static int	val;

	if (value == -69)
		return (val);
	val = value;
	return (value);
}

void	set(int value)
{
	handle_value(value);
}

int	get(void)
{
	return (handle_value(-69));
}
