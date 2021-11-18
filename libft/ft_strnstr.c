/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 11:45:54 by wollio            #+#    #+#             */
/*   Updated: 2021/11/09 14:55:22 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (*haystack && len--)
	{
		i = 0;
		l = len + 1;
		while (haystack[i] && needle[i] && haystack[i] == needle[i] && l--)
			i++;
		if (i == ft_strlen(needle))
			return (((char *)haystack));
		haystack++;
	}
	return (NULL);
}

int	ft_strnstr_2(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return (0);
	i = 0;
	j = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j]
			&& needle[j] != '\0' && haystack[i] != '\0' && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
