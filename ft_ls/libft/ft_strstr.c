/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 07:58:35 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 07:59:35 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*cp_haystack;
	const char	*cp_needle;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		while (*haystack && *needle && *haystack != *needle)
			haystack++;
		if (!*haystack)
			return (NULL);
		cp_haystack = haystack;
		cp_needle = needle;
		while (*cp_haystack && *cp_needle && *cp_haystack == *cp_needle)
		{
			cp_haystack++;
			cp_needle++;
		}
		if (!*cp_needle)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
