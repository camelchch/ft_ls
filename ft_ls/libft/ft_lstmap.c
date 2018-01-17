/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:50:34 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/14 13:40:59 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cp_lst;
	t_list	*result;

	if (lst != NULL)
	{
		if (!(cp_lst = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		cp_lst = f(lst);
		result = cp_lst;
		while (lst->next != NULL)
		{
			if (!(cp_lst->next = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			lst = lst->next;
			cp_lst->next = f(lst);
			cp_lst = cp_lst->next;
		}
		return (result);
	}
	return (NULL);
}
