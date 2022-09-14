/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:20:40 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/10 11:36:54 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	unsigned char	ch;

	ch = (unsigned char) c;
	if (ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t'
		|| ch == '\v')
		return (1);
	return (0);
}

static int	big_num(int sign, int res, char digit)
{
	int	max;
	int	max_div;
	int	int_digit;

	int_digit = digit - '0';
	max_div = 7;
	if (sign < 0)
		max_div++;
	max = 214748364;
	if (max > res)
		return (1);
	if (int_digit > max_div)
	{
		if (sign > 0)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	is_big_num;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		is_big_num = big_num(sign, result, *str);
		if (is_big_num <= 0)
			return (is_big_num);
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
