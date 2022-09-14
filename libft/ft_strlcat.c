/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:03:22 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/10 10:03:22 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (i < size && dst[i])
		i++;
	while (src[n] && ((i + n + 1) < size))
	{
		dst[i + n] = src[n];
		n++;
	}
	if (i < size)
		dst[i + n] = '\0';
	return (i + ft_strlen(src));
}
