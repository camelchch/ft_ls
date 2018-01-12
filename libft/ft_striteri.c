/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:55:30 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/13 17:24:16 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned	int	index;

	index = 0;
	if (s && f)
	{
		while (*(s + index))
		{
			f(index, s + index);
			index++;
		}
	}
}
