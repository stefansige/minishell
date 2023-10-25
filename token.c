/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:16:10 by snovakov          #+#    #+#             */
/*   Updated: 2023/10/18 12:16:12 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isact(int n)
{
	if (n >= 3 && n <= 7)
		return (1);
	return (0);
}

int	ft_isarg(int i)
{
	if (i == 0 || i == 8 || i == 9)
		return (1);
	else
		return (0);
}

int	ft_checkred(t_shell *s)
{
	if (ft_isarg(s->t[s->i + 1].type))
	{
		if (s->t[s->i + 1].type == 4 || s->t[s->i + 1].type == 6)
		{
			if (access(s->t[s->i + 1].tok, W_OK) != 0)
				return (1);
		}
		else if (s->t[s->i + 1].type == 5)
		{
			if (access(s->t[s->i + 1].tok, R_OK) != 0)
				return (1);
		}
		s->t[s->i + 1].type = 10;
		return (0);
	}
	else 
		return (1);
}

int	ft_setact(t_shell *s, int ver)
{
	if ((s->i == 0 || s->t[s->i + 1].tok == NULL) && ver == 3)
	{
		ft_berror(s);
		return (1);
	}
	if (s->t[s->i].type >= 4 && s->t[s->i].type <= 7)
		if (ft_checkred(s))
		{
			ft_perror(s);
			return (1);
		}
	s->nb = s->i;
	s->nb--;
	while (s->nb >= 0 && !ft_isact(s->t[s->nb].type))
	{
		if (s->t[s->nb].type == 1)
		{
			s->t[s->nb].pfd = ver;
			s->nb = -1;
		}
		s->nb--;
	}
	s->i++;
	return (0);
}

int	ft_token(t_shell *s)
{
	s->i = 0;
	s->nb = 0;
	while (s->t[s->i].tok)
	{
		if (s->t[s->i].type == 0)
		{
			s->t[s->i].type = 1;
			s->i++;
			while (s->t[s->i].tok && ft_isarg(s->t[s->i].type))
			{
				s->t[s->i].type = 2;
				s->i++;
			}
		}
		else if (ft_isact(s->t[s->i].type))
		{
			if (ft_setact(s, s->t[s->i].type))
				return (0);
		}
		else
			s->i++;
	}
	return (1);
}