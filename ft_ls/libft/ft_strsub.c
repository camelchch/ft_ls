/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:16:21 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/10 16:21:40 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (s)
	{
		i = 0;
		if (!(result = (char *)malloc(len + 1)))
			return (NULL);
		while (i < len)
			result[i++] = s[start++];
		result[i] = '\0';
		return (result);
	}
	return (NULL);
}
