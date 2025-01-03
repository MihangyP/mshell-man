/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:36:51 by irazafim          #+#    #+#             */
/*   Updated: 2024/12/26 20:27:36 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_newstr;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_newstr = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = (char *)malloc(len_newstr);
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1, len_newstr);
	ft_strlcat(newstr, s2, len_newstr);
	return (newstr);
}
