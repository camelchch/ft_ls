/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:31:18 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:03:19 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	unsigned	char	*nptr_cp;
	int					neg_or_pos;
	long				result;

	neg_or_pos = 1;
	result = 0;
	nptr_cp = (unsigned char *)nptr;
	while (*nptr_cp == '\t' || *nptr_cp == '\v' || *nptr_cp == '\f'
			|| *nptr_cp == '\n' || *nptr_cp == '\r' || *nptr_cp == ' ')
		nptr_cp++;
	if (*nptr_cp == '-' || *nptr_cp == '+')
	{
		if (*nptr_cp == '-')
			neg_or_pos = -1;
		nptr_cp++;
	}
	while (*nptr_cp && *nptr_cp >= '0' && *nptr_cp <= '9' && result >= 0)
		result = result * 10 + *nptr_cp++ - '0';
	if (result < 0 && neg_or_pos == 1)
		return (-1);
	if (result < 0 && neg_or_pos == -1)
		return (0);
	result = result * neg_or_pos;
	return ((int)result);
}
