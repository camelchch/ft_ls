/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 00:11:25 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 08:55:41 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int	nb_digit_itoa(int n)
{
	int				i;
	unsigned	int	nb;

	i = 1;
	if (n < 0)
	{
		i = 2;
		nb = (unsigned int)n * -1;
	}
	else
		nb = (unsigned int)n;
	while (nb > 9)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char			*number;
	int				len;
	unsigned	int	cp_n;

	len = nb_digit_itoa(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (unsigned int)n * -1;
	}
	else
		cp_n = (unsigned int)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}
