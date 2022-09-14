/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:04:42 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/17 11:50:09 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res_list;
	t_list	*new_elem;

	if (!f || !del)
		return (NULL);
	res_list = NULL;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst -> content));
		if (!new_elem)
		{
			ft_lstclear(&res_list, del);
			return (NULL);
		}
		ft_lstadd_back(&res_list, new_elem);
		lst = lst -> next;
	}
	return (res_list);
}
