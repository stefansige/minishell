/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:31:18 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:31:20 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isact(int n)
{
	if (n >= 3 && n <= 7)
		return (1);
	return (0);
}

int	ft_setoutput(t_shell *s, int ver)
{
	s->nb = s->i - 1;
	while (s->nb >= 0 && s->t[s->nb].type != 3)
	{
		if (s->t[s->nb].type == 1)
		{
			if (ver == 1)
				s->t[s->nb].output = open(s->t[s->i + 1].tok,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				s->t[s->nb].output = open(s->t[s->i + 1].tok,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			return (0);
		}
		s->nb--;
	}
	return (0);
}

int	ft_setinput(t_shell *s)
{
	if (s->i == 0)
	{
		close(s->import);
		s->import = open(s->t[s->i + 1].tok, O_RDONLY);
	}
	s->nb = s->i - 1;
	while (s->nb >= 0 && s->t[s->nb].type != 3)
	{
		if (s->t[s->nb].type == 1)
		{
			s->t[s->nb].input = open(s->t[s->i + 1].tok, O_RDONLY);
			return (0);
		}
		s->nb--;
	}
	return (0);
}

void	ft_disable(t_shell *s)
{
	int	i;

	i = s->i - 1;
	while (i >= 0 && s->t[i].type != 3)
	{
		if (s->t[i].type == 1)
		{
			s->t[i].type = -1;
			return ;
		}
		i--;
	}
}

int	ft_checkoutput(t_shell *s)
{
	if (access(s->t[s->i + 1].tok, F_OK) != 0)
		return (ft_setoutput(s, 0));
	else if (access(s->t[s->i + 1].tok, W_OK) != 0)
	{
		printf("%s: Permission denied\n", s->t[s->i + 1].tok);
		s->exit = 1;
		ft_disable(s);
		return (0);
	}
	else if (s->t[s->i].type == 4)
		return (ft_setoutput(s, 0));
	else if (s->t[s->i].type == 6)
		return (ft_setoutput(s, 1));
	return (0);
}
