/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 07:44:13 by nmordeka          #+#    #+#             */
/*   Updated: 2022/03/27 14:31:18 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **dlst, void (*del)(void *))
{
	t_dlist	*tmp;

	while (*dlst)
	{
		if ((*dlst)->content)
			del((*dlst)->content);
		tmp = *dlst;
		*dlst = tmp->next;
		free(tmp);
	}
	dlst = NULL;
}
