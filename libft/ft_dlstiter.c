/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 08:18:44 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/17 12:09:52 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstiter(t_dlist *dlst, void (*f)(void *))
{
	t_dlist	*start;

	if (!dlst || !f)
		return ;
	start = dlst;
	while (FT_TRUE)
	{
		if (dlst->content)
			f(dlst->content);
		dlst = dlst ->next;
		if (!dlst || dlst == start)
			break ;
	}
}
