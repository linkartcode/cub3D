/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:30:09 by nmordeka          #+#    #+#             */
/*   Updated: 2021/11/14 12:43:55 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	const char	*source;
	char		*dest;
	size_t		max_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	source = s + start;
	max_len = ft_strlen(source);
	if (max_len < len)
		len = max_len;
	substr = malloc(sizeof(*substr) * (len + 1));
	if (!substr)
		return (NULL);
	dest = substr;
	while (source && len--)
		*dest++ = *source++;
	*dest = '\0';
	return (substr);
}
