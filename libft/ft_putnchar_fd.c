/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:12:38 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/29 14:27:23 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnchar_fd(size_t n, char ch, int fd)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{	
		while (i < n)
		{
			ft_putchar_fd(ch, fd);
			i++;
		}
	}
	return (i);
}
