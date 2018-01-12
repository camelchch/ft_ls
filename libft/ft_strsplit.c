/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:33:42 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 13:45:26 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

unsigned	int		ft_nbwords(char const *s, char c)
{
	unsigned	int	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static char			*ft_fillwords(unsigned int l, char const *str)
{
	char			*s;
	unsigned int	j;
	unsigned int	i;

	if (!(s = (char *)malloc(sizeof(char) * l + 1)))
		return (NULL);
	j = 0;
	i = 0;
	while (j < l && str[i])
	{
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	return (s);
}

unsigned	int		wc(char const *s, char c)
{
	unsigned	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**as;
	unsigned	int	i;
	unsigned	int	len;
	unsigned	int	y;

	i = 0;
	if (s != NULL)
	{
		y = wc(s, c);
		if (!(as = (char **)malloc(sizeof(char *) * (wc(s, c) + 1))))
			return (NULL);
		while (i < y && *s)
		{
			while (*s && *s == c)
				s++;
			len = ft_nbwords(s, c);
			as[i] = ft_fillwords(len, s);
			s = (s + len);
			i++;
		}
		as[i] = 0;
		return (as);
	}
	return (NULL);
}
