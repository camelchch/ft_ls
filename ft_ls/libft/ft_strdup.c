/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:22:55 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:23:25 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = 0;
	if (!(copy = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (*s)
		copy[i++] = *s++;
	copy[i] = '\0';
	return (copy);
}
