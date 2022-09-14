/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:45:31 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/10 10:45:31 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recurs(int nbr, int fd)
{
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_recurs(-nbr, fd);
	}
	else if (nbr > 9)
	{
		ft_putnbr_recurs(nbr / 10, fd);
		ft_putnbr_recurs(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n != -2147483648)
		ft_putnbr_recurs(n, fd);
	else
		ft_putstr_fd("-2147483648", fd);
}
