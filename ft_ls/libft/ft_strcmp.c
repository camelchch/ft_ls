/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:22:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:22:36 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned	char	*cp_s1;
	unsigned	char	*cp_s2;

	cp_s1 = (unsigned char *)s1;
	cp_s2 = (unsigned char *)s2;
	while (*cp_s1 && *cp_s2 && *cp_s1 == *cp_s2)
	{
		cp_s1++;
		cp_s2++;
	}
	return (*cp_s1 - *cp_s2);
}
