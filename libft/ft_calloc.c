/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:25:00 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/10 10:25:00 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	char	*res;

	if (n == 0 || size == 0)
	{
		n = 1;
		size = 1;
	}
	size = size * n;
	res = malloc(size);
	if (res)
		ft_bzero(res, size);
	return (res);
}
