/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:33:39 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 08:04:08 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	end;
	char	*result;

	i = 0;
	if (s)
	{
		end = ft_strlen(s) - 1;
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		while (end != 0 && end >= i && (s[end] == ' ' || s[end] == '\t' \
					|| s[end] == '\n'))
			end--;
		if (!(result = (char *)malloc(end - i + 2)))
			return (NULL);
		result = ft_strncpy(result, s + i, end - i + 1);
		result[end - i + 1] = '\0';
		return (result);
	}
	return (NULL);
}
