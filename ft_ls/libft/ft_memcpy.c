/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:13:06 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:13:57 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned	char			*byte_dest;
	const	unsigned	char	*byte_src;

	byte_dest = dest;
	byte_src = src;
	while (n-- > 0)
		*byte_dest++ = (unsigned char)*byte_src++;
	return (dest);
}
