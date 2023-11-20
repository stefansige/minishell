/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:28:20 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 19:28:22 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getenv_n(char **env, char *s)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (env && s[j] && env[i] && env[i][j])
	{
		if (env[i][j] != s[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	if (!env[i] || !s || j != ft_strlen(s))
		return (0);
	return (i);
}

bool	ft_has_equal(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (true);
	}
	return (false);
}

bool	ft_isvarn(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (false);
	while (str[i])
	{
		if (i != 0 && str[i] == '=')
			return (true);
		if (!((str[i] >= '0' && str[i] <= '9')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] == '_') || (str[i] == '=')))
			return (false);
		else
			i++;
	}
	return (true);
}

void	ft_unset(t_shell *s)
{
	int		i;
	char	*tmp;

	s->exit = 0;
	i = 0;
	while (s->t[s->i].arg[++i])
	{
		if (ft_isvarn(s->t[s->i].arg[i]) && !(ft_has_equal(s->t[s->i].arg[i])))
		{
			tmp = ft_getenv(s->env, s->t[s->i].arg[i]);
			if (tmp)
			{
				free (tmp);
				ft_unset_real(s, s->t[s->i].arg[i]);
			}
		}
		else
		{
			printf("unset: `%s': not a valid identifier\n", s->t[s->i].arg[i]);
			s->exit = 1;
		}
	}
}

void	ft_export_arg_len(char *arg, int *nlen, int *clen)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	nlen[0] = i;
	while (arg[i])
		i++;
	clen[0] = i - nlen[0] - 1;
}
