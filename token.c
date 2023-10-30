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

void	ft_setoutput(t_shell *s)
{
	s->nb = s->i - 1;
	while (s->nb >= 0 && s->t[s->nb].type != 3)
	{
		if (s->t[s->nb].type == 1)
		{
			s->t[s->nb].output = open()
			return ;
		}
		s->nb--;
	}
}

void	ft_setinput(t_shell *s)
{
	s->nb = s->i - 1;
	while (s->nb >= 0 && s->t[s->nb].type != 3)
	{
		if (s->t[s->nb].type == 1)
		{
			s->t[s->nb].input = ft_strcpy(s->t[s->i + 1].tok);
			return ;
		}
		s->nb--;
	}
}

int	ft_checkred(t_shell *s)
{
	if (ft_isarg(s->t[s->i + 1].type))
	{
		if (s->t[s->i].type == 4 || s->t[s->i].type == 6)
		{
			if (access(s->t[s->i + 1].tok, F_OK) != 0)
			{
				ft_setoutput(s, 1);
				return (0);
			}
			else if (access(s->t[s->i + 1].tok, W_OK) != 0)
				return (ft_perror(s));
			ft_setoutput(s, 0);
		}
		else if (s->t[s->i + 1].type == 5)
		{
			if (access(s->t[s->i + 1].tok, R_OK) != 0)
				return (ft_perror(s));
			ft_setinput(s);
		}
		s->t[s->i + 1].type = 10;
		return (0);
	}
	else
		return (ft_berror(s));
}

int	ft_checkpipe(t_shell *s)
{
	if (s->i == 0 || s->t[s->i + 1].tok == NULL)
	{
		ft_berror(s);
		return (1);
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
		else if (s->t[s->i].type == 3)
		{
			if (ft_checkpipe(s))
				return (0);
		}
		else if (s->t[s->i].type >= 4 && s->t[s->i].type <= 7)
		{
			if (ft_checkred(s))
				return (0);
		}
		else
			s->i++;
	}
	return (1);
}
