/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:43:56 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/13 15:22:12 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_substrn(char **dest, char **srcs)
{
	char	*new_srcs;
	size_t	counter;

	counter = 0;
	if (!*srcs)
		*srcs = ft_strdup("");
	while ((*srcs)[counter] != '\n' && (*srcs)[counter])
		counter++;
	if ((*srcs)[counter] == '\n')
	{
		*dest = ft_substr(*srcs, 0, counter + 1);
		new_srcs = ft_strdup(*srcs + counter + 1);
		free(*srcs);
		*srcs = new_srcs;
		if (!**srcs)
		{
			free(*srcs);
			*srcs = NULL;
		}
		return (1);
	}
	*dest = *srcs;
	*srcs = NULL;
	return (0);
}

static char	*get_buf_str(int fd)
{
	char	*buf_str;
	int		n_read;

	buf_str = malloc(BUFFER_SIZE + 1);
	if (!buf_str)
		return (NULL);
	n_read = read(fd, buf_str, BUFFER_SIZE);
	if (n_read <= 0)
	{
		free(buf_str);
		return (NULL);
	}
	buf_str[n_read] = '\0';
	return (buf_str);
}

static void	sum_str(char **sum_str, char *add_str)
{
	char	*newstr;

	newstr = ft_strjoin(*sum_str, add_str);
	free(*sum_str);
	*sum_str = newstr;
}

char	*get_next_line(int fd)
{
	static char	*str_holder = NULL;
	char		*out_str;
	char		*tmp_str;
	int			exit_flag;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX_INT - 1)
		return (NULL);
	if (get_substrn(&out_str, &str_holder))
		return (out_str);
	str_holder = get_buf_str(fd);
	while (str_holder)
	{
		exit_flag = get_substrn(&tmp_str, &str_holder);
		sum_str(&out_str, tmp_str);
		free(tmp_str);
		if (exit_flag)
			return (out_str);
		str_holder = get_buf_str(fd);
	}
	if (*out_str)
		return (out_str);
	free(out_str);
	return (NULL);
}
