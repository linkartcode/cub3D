/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 08:08:54 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/27 14:10:11 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*last;

	if (dlst)
	{
		if (*dlst && new)
		{
			last = (*dlst);
			while (last->next)
				last = last->next;
			last->next = new;
			new->prev = last;
		}
		else
			*dlst = new;
	}
}
