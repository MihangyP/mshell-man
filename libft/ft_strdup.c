/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:51:08 by irazafim          #+#    #+#             */
/*   Updated: 2024/12/26 20:27:24 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new_str;

	if (src == NULL)
		return (NULL);
	new_str = (char *)malloc(ft_strlen(src) + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, src, ft_strlen(src) + 1);
	return (new_str);
}
