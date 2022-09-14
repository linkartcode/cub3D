/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:22:15 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/10 10:22:15 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_tmp;
	const unsigned char	*s2_tmp;
	int					res;

	i = 0;
	s1_tmp = s1;
	s2_tmp = s2;
	if (n > 0)
	{
		while (i < n)
		{
			res = *s1_tmp - *s2_tmp;
			if (res)
				return (res);
			s1_tmp++;
			s2_tmp++;
			i++;
		}
	}
	return (0);
}
