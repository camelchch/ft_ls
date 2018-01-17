/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:45:06 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:30:04 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_string;
	unsigned	int	i;

	if (s && f)
	{
		i = 0;
		if (!(new_string = (char *)malloc(ft_strlen(s) + 1)))
			return (NULL);
		while (*(s + i))
		{
			*(new_string + i) = f(i, *(s + i));
			i++;
		}
		*(new_string + i) = '\0';
		return (new_string);
	}
	return (NULL);
}
