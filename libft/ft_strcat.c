/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:20:14 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:20:29 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	length;

	length = ft_strlen(dest);
	while (*src)
		dest[length++] = *src++;
	dest[length] = *src;
	return (dest);
}
