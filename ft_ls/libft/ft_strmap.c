/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:31:07 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:28:18 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new_string;
	int		i;

	if (s && f)
	{
		i = 0;
		if (!(new_string = (char *)malloc(ft_strlen(s) + 1)))
			return (NULL);
		while (*s)
			*(new_string + i++) = f(*s++);
		*(new_string + i) = '\0';
		return (new_string);
	}
	return (NULL);
}
