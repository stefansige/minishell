/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:18:58 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 15:19:00 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compare(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2 || (!s1[0] && !s2[0]))
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

int	ft_isbuiltin2(t_shell *s, int ver)
{
	if (ft_compare(s->t[s->i].tok, "export") && s->t[s->i].arg[1])
	{
		if (ver == 1)
			ft_export(s);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "unset"))
	{
		if (ver == 1)
			ft_unset(s);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "cd"))
	{
		if (ver == 1)
			ft_cd(s);
		return (1);
	}
	return (0);
}

int	ft_isbuiltin(t_shell *s, int ver)
{
	if (ft_compare(s->t[s->i].tok, "echo"))
	{
		if (ver == 1)
			s->exit = ft_echo(s->t[s->i].arg);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "pwd"))
	{
		if (ver == 1)
			s->exit = ft_pwd(s->t[s->i].arg, s->env);
		return (1);
	}
	else if (ft_compare(s->t[s->i].tok, "env"))
	{
		if (ver == 1)
			s->exit = ft_env(s->t[s->i].arg, s->env);
		return (1);
	}
	if (ft_compare(s->t[s->i].tok, "export"))
	{
		if (ver == 1 && !s->t[s->i].arg[1])
			s->exit = ft_export_forth(s->env);
		return (1);
	}
	return (0);
}
