/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:48 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 15:05:50 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find(t_shell *s, int i)
{
	int	y;
	int	z;
	int	j;

	y = i;
	z = 0;
	j = 0;
	while (s->env[z] && s->env[z][j] && ft_isvname(s->l[y]))
	{
		if (s->env[z][j] != s->l[y])
		{
			z++;
			y = i;
			j = 0;
		}
		else
		{
			j++;
			y++;
		}
	}
	if (s->env[z] && s->env[z][j] == '=')
		return (s->l = ft_adddol(s->l, i, s->env[z]));
	else
		return (s->l = ft_rmdol(s->l, i - 1));
}

static int	nbr_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		n_len;
	long	n_long;

	n_long = n;
	n_len = nbr_len(n_long);
	str = malloc((n_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n_long == 0)
		str[0] = '0';
	if (n_long < 0)
	{
		n_long *= -1;
		str[0] = '-';
	}
	str[n_len] = '\0';
	while (n_long > 0)
	{
		str[n_len-- - 1] = (n_long % 10) + 48;
		n_long /= 10;
	}
	return (str);
}

void	ft_exitdol(t_shell *s, int i)
{
	char	*exit;
	char	*ret;
	int		y;
	int		k;

	exit = ft_itoa(s->exit);
	ret = ft_calloc(sizeof(char), (ft_strlen(s->l) + ft_strlen(exit) - 1));
	y = 0;
	while (s->l[y] && y != i)
	{
		ret[y] = s->l[y];
		y++;
	}
	k = 0;
	while (exit[k])
		ret[y++] = exit[k++];
	free(exit);
	k = i + 2;
	while (s->l[k])
		ret[y++] = s->l[k++];
	free(s->l);
	s->l = ret;
}

void	ft_dollar(t_shell *s)
{
	int	i;

	i = 0;
	while (s->l && s->l[i])
	{
		if (s->l[i] == '\'')
		{
			i++;
			while (s->l[i] && s->l[i] != '\'')
				i++;
		}
		if (s->l[i] == '$' && ft_isvname(s->l[i + 1]))
		{
			s->l = ft_find(s, i + 1);
			i = 0;
		}
		else if (s->l[i] == '$' && s->l[i + 1] == '?')
			ft_exitdol(s, i);
		else
			i++;
	}
}
