/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:49:13 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:49:14 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvname(char c)
{
	if (c && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z') || (c == '_')))
		return (1);
	else
		return (0);
}

char	*ft_adddol(char *l, int i, char *env)
{
	int		y;
	int		k;
	char	*ret;

	y = 0;
	while (env[y] != '=')
		y++;
	ret = ft_calloc(sizeof(char),
			(ft_strlen(env) - y) + (ft_strlen(l) - ft_dolen(l, i) - 1));
	y++;
	k = 0;
	while (k < (i - 1))
	{
		ret[k] = l[k];
		k++;
	}
	i = i + ft_dolen(l, i);
	while (env[y])
		ret[k++] = env[y++];
	while (l[i])
		ret[k++] = l[i++];
	free (l);
	return (ret);
}

char	*ft_rmdol(char *l, int i)
{
	char	*new;
	int		y;
	int		z;

	y = 0;
	z = 0;
	new = ft_calloc(sizeof(char),
			((ft_strlen(l) - (ft_dolen(l, i + 1) + 1)) + 1));
	while (l[y] && new)
	{
		if (y == i)
		{
			y++;
			while (ft_isvname(l[y]))
				y++;
		}
		else
		{
			new[z] = l[y];
			y++;
			z++;
		}
	}
	free(l);
	return (new);
}
