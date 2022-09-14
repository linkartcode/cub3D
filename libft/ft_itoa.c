/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:21:17 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/11 16:21:17 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill_str(char *str, int n, int size)
{
	while (n > 9)
	{
		str[size] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	str[size] = n + '0';
	return ;
}

static char	*getalloc_str(char *str)
{
	size_t	len;
	size_t	i;
	char	*res_str;

	len = ft_strlen(str);
	res_str = malloc(sizeof(*str) * (len + 1));
	if (!res_str)
		return (0);
	i = 0;
	while (i < len)
	{
		res_str[i] = str[i];
		i++;
	}
	res_str[i] = '\0';
	return (res_str);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*res_str;

	if (n == 0)
		return (getalloc_str("0"));
	else if (n == -2147483648)
		return (getalloc_str("-2147483648"));
	size = get_size(n);
	res_str = malloc((size + 1) * sizeof(*res_str));
	if (res_str)
	{
		if (n < 0)
		{
			*res_str = '-';
			n = -n;
		}
		res_str[size] = '\0';
		fill_str(res_str, n, size - 1);
	}
	return (res_str);
}
