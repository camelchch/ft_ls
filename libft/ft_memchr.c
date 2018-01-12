/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:12:40 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 10:47:03 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *copy;
	size_t				i;

	i = 0;
	copy = s;
	while (i < n)
	{
		if (*copy == (unsigned char)c)
			return ((void *)copy);
		copy++;
		i++;
	}
	return (NULL);
}
