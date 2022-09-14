/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 08:12:31 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/17 08:14:18 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dlstsize(t_dlist *dlst)
{
	size_t	size;
	t_dlist	*start;

	if (!dlst)
		return (0);
	size = 1;
	start = dlst;
	dlst = dlst->next;
	while (dlst && dlst != start)
	{
		dlst = dlst ->next;
		size++;
	}
	return (size);
}
