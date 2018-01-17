/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:26:26 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 15:59:53 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	char		*dst;
	const char	*sc;
	size_t		i;
	size_t		dstlen;

	dst = dest;
	sc = src;
	i = n;
	while (i-- != 0 && *dst != '\0')
		dst++;
	dstlen = dst - dest;
	i = n - dstlen;
	if (i == 0)
		return (dstlen + (ft_strlen(sc)));
	while (*sc)
	{
		if (i != 1)
		{
			*dst++ = *sc;
			i--;
		}
		sc++;
	}
	*dst = '\0';
	return (dstlen + (sc - src));
}
