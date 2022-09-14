/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:34:26 by nmordeka          #+#    #+#             */
/*   Updated: 2021/11/14 12:44:22 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join_str;

	if (!s1 || !s2)
		return (NULL);
	join_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*s1));
	if (!join_str)
		return (NULL);
	i = -1;
	while (s1[++i])
		join_str[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		join_str[i] = s2[j];
		i++;
	}
	join_str[i] = '\0';
	return (join_str);
}
