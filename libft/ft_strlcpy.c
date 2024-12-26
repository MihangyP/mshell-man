/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 07:35:47 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/26 17:04:30 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_src);
}

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	src_len;

// 	src_len = ft_strlen(src);
// 	if (size == 0)
// 		return (src_len);
// 	if (size > src_len + 1)
// 		ft_memcpy(dst, src, src_len + 1);
// 	else
// 	{
// 		ft_memcpy(dst, src, size - 1);
// 		dst[size - 1] = '\0';
// 	}
// 	return (src_len);
// }
