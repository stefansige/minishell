/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:45:05 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:45:07 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rereset(char *varn, char *varc)
{
	char	*re;
	int		i;
	int		j;

	i = 0;
	j = 0;
	re = NULL;
	re = (char *)ft_calloc(sizeof(char),
			(ft_strlen(varn) + ft_strlen(varc) + 2));
	while (varn && varn[i])
	{
		re[i] = varn[i];
		i++;
	}
	re[i++] = '=';
	while (varc && varc[j])
	{
		re[i] = varc[j];
		i++;
		j++;
	}
	re[i] = '\0';
	return (re);
}

bool	ft_env_check(char *var)
{
	int	i;

	i = 0;
	while (var && var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	ft_env(char **arg, char **env)
{
	int	i;

	(void)arg;
	i = -1;
	while (env[++i])
	{
		if (ft_env_check(env[i]))
			printf("%s\n", env[i]);
	}
	return (0);
}
