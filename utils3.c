/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:29:03 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:29:05 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *str1, char *str2)
{
	char	*res;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!str1 && !str2)
		return (NULL);
	res = ft_calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 2));
	while (str1 && str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	res[i] = '/';
	i++;
	while (str2 && str2[k])
	{
		res[i] = str2[k];
		i++;
		k++;
	}
	return (res);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		k;

	i = 0;
	k = 0;
	join = NULL;
	join = ft_calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 2));
	while (str1 && str1[i])
	{
		join[i] = str1[i];
		i++;
	}
	while (str2 && str2[k])
	{
		join[i] = str2[k];
		i++;
		k++;
	}
	join[i] = '\n';
	return (join);
}

int	ft_isdir(char *s)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	ft_islash(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_dpstrlen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
