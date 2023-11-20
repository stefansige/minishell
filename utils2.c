/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:26:30 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:26:32 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *s)
{
	char	*cpy;
	int		i;

	if (!s)
		return (NULL);
	cpy = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	return (cpy);
}

void	ft_free(char **s)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	ft_isspace(const char c)
{
	if (c == 32 || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr)
	{
		if (!(*nptr >= '0' && *nptr <= '9'))
			return (-1010101);
		n *= 10;
		n += (*nptr - 48);
		nptr++;
	}
	return (n * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
