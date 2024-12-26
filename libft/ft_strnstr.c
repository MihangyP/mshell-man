/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:27:11 by irazafim          #+#    #+#             */
/*   Updated: 2024/12/26 20:34:23 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const void *big, const char *little, size_t len)
{
	size_t	i;
	char	*b;

	b = (char *) big;
	if (!*little)
		return (b);
	i = 0;
	while (i < len && b[i] != '\0')
	{
		if (b[i] == little[0])
		{
			if ((ft_strncmp(b + i, little, ft_strlen(little)) == 0)
				&& i + ft_strlen(little) <= len)
				return (b + i);
		}
		i++;
	}
	return (NULL);
}
