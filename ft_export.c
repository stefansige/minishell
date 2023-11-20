/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:41:47 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:41:49 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_export_arg(char *arg, char **varn, char **varc)
{
	int	i;
	int	nlen;
	int	clen;

	i = 0;
	ft_export_arg_len(arg, &nlen, &clen);
	if (nlen > 0)
		(*varn) = (char *)ft_calloc(sizeof(char), nlen + 1);
	if (clen > 0)
		(*varc) = (char *)ft_calloc(sizeof(char), clen + 1);
	while (i < nlen)
	{
		(*varn)[i] = arg[i];
		i++;
	}
	i = 0;
	while (i < clen)
	{
		(*varc)[i] = arg[i + nlen + 1];
		i++;
	}
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] != '\0')
		i++;
	dst = malloc(sizeof(char) * i + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_set(t_shell *s, char *varn, char *varc)
{
	char	**new_env;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s->env[len] != NULL)
		len++;
	new_env = ft_calloc(sizeof(char *), len + 2);
	while (s->env[i] != NULL)
	{
		new_env[i] = s->env[i];
		i++;
	}
	if (varc)
		new_env[i] = ft_rereset(varn, varc);
	else
		new_env[i] = ft_strdup(varn);
	free(s->env);
	s->env = new_env;
}

void	ft_export2(t_shell *s, int i)
{
	char	*varn;
	char	*varc;
	char	*tmp;

	varn = NULL;
	varc = NULL;
	ft_read_export_arg(s->t[s->i].arg[i], &varn, &varc);
	tmp = ft_getenv(s->env, varn);
	if (tmp)
	{
		ft_reset(s->env, varn, varc);
		free(tmp);
	}
	else if (!tmp)
		ft_set(s, varn, varc);
	if (varc)
		free(varc);
	if (varn)
		free(varn);
}

void	ft_export(t_shell *s)
{
	int		i;

	s->exit = 0;
	i = 0;
	while (s->t[s->i].arg[++i])
	{
		if (ft_isvarn(s->t[s->i].arg[i]) && s->t[s->i].arg[i][0] != '='
				&& s->t[s->i].arg[1][0])
			ft_export2(s, i);
		else
		{
			printf("export: `%s': not a valid identifier\n", s->t[s->i].arg[i]);
			s->exit = 1;
		}
	}
}
