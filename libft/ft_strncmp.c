/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:42:15 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 07:56:30 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned	char	*cp_s1;
	unsigned	char	*cp_s2;

	cp_s1 = (unsigned char *)s1;
	cp_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*cp_s1 && *cp_s2 && *cp_s1 == *cp_s2 && n > 1)
	{
		cp_s1++;
		cp_s2++;
		n--;
	}
	return (*cp_s1 - *cp_s2);
}
