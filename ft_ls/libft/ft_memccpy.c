/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:27:19 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:12:30 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void	*restrict dest, const void *restrict src,
		int c, size_t n)
{
	unsigned	char			*byte_dest;
	const	unsigned	char	*byte_src;

	byte_dest = dest;
	byte_src = src;
	while (n--)
	{
		*byte_dest++ = *byte_src++;
		if (*(byte_src - 1) == (unsigned char)c)
			return (byte_dest);
	}
	return (NULL);
}
