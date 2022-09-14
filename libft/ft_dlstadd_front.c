/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 07:57:43 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/17 08:35:26 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*last;

	if (*dlst && new)
	{
		if ((*dlst)->next == NULL)
		{
			(*dlst)->next = new;
			new -> prev = *dlst;
		}
		else
		{
			last = (*dlst)->prev;
			last->next = new;
			new->prev = last;
		}
		new -> next = *dlst;
		(*dlst)->prev = new;
		*dlst = new;
	}
}
