/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:36:52 by snovakov          #+#    #+#             */
/*   Updated: 2022/11/14 19:52:50 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *a, char *b)
{
	char		*strjoin;
	size_t		i;
	size_t		y;

	if (!a)
	{
		a = (char *)malloc(sizeof(char) * 1);
		a[0] = '\0';
	}
	if (!a || !b)
		return (NULL);
	strjoin = (char *)malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 1));
	if (!strjoin)
		return (NULL);
	i = -1;
	y = 0;
	if (a)
		while (a[++i])
			strjoin[i] = a[i];
	while (b[y])
		strjoin[i++] = b[y++];
	strjoin[i] = '\0';
	free(a);
	return (strjoin);
}
