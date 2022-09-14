/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:08:11 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/18 10:03:25 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist **dlst, void (*del)(void *))
{
	t_dlist	*next_node;
	t_dlist	*last_node;

	next_node = NULL;
	if (del && dlst && *dlst)
	{
		if (ft_dlstsize(*dlst) > 1)
		{
			next_node = (*dlst)->next;
			last_node = (*dlst)->prev;
			last_node -> next = next_node;
			next_node -> prev = last_node;
		}
		if ((*dlst)->content)
			(*del)((*dlst)->content);
		free(*dlst);
		*dlst = next_node;
	}
}
