/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:28:05 by nmordeka          #+#    #+#             */
/*   Updated: 2021/11/14 12:44:43 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup_str;

	dup_str = malloc((ft_strlen(s) + 1) * sizeof(*s));
	if (dup_str)
	{
		i = -1;
		while (s[++i])
			dup_str[i] = s[i];
		dup_str[i] = '\0';
	}
	return (dup_str);
}
