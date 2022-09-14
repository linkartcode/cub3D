/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 23:11:59 by nmordeka          #+#    #+#             */
/*   Updated: 2021/10/18 16:51:23 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_str(char const *s, const char c)
{
	char	set[2];
	char	*substr;

	set[0] = c;
	set[1] = '\0';
	substr = ft_strtrim(s, set);
	if (!substr)
		return (0);
	if (!(*substr))
	{
		free(substr);
		return (0);
	}
	return (substr);
}

static size_t	get_n(char const *s, const char c)
{
	int		count;
	int		i;
	char	*substr;

	substr = trim_str(s, c);
	if (!substr)
		return (0);
	count = 1;
	i = 0;
	while (substr[i])
	{
		if (substr[i] == c)
		{
			count++;
			while (substr[i] == c)
				i++;
		}
		else
			i++;
	}
	free(substr);
	return (count);
}

static void	free_malloc(char **split_arr, size_t count)
{
	size_t	i;

	if (!split_arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

static int	fill_arr(char **split_arr, const char *s, char c, size_t count)
{
	size_t	i;
	size_t	str_counter;
	size_t	start_substr;
	size_t	len_str;

	i = 0;
	str_counter = 0;
	while (i < count && s[str_counter])
	{
		start_substr = str_counter;
		while (s[str_counter] != c && s[str_counter])
			str_counter++;
		len_str = str_counter - start_substr;
		split_arr[i] = ft_substr(s, start_substr, len_str);
		if (!split_arr[i])
		{
			free_malloc(split_arr, i);
			return (0);
		}
		while (s[str_counter] == c)
			str_counter++;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	ncount;
	char	**split_arr;
	size_t	tmp;

	if (!s)
		return (0);
	if (!(*s))
		ncount = 0;
	else
		ncount = get_n(s, c);
	split_arr = malloc (sizeof(s) * (ncount + 1));
	if (!split_arr)
		return (0);
	if (ncount)
	{
		while (*s == c)
			s++;
		tmp = fill_arr(split_arr, s, c, ncount);
		if (tmp != ncount)
			return (0);
	}
	split_arr[ncount] = 0;
	return (split_arr);
}
