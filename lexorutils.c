/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexorutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:14 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 17:07:15 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if ((line[i] < 32 && line[i] > 13) || line[i] < 7)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_iss(char c)
{
	if (c == 32 || (c <= 13 && c >= 8))
		return (1);
	else
		return (0);
}

int	ft_ism(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	ft_qplus(t_shell *s, char c)
{
	s->i++;
	while (s->l[s->i] && s->l[s->i] != c)
	{
		if (s->l[s->i])
			s->i++;
		s->k++;
	}
	if (!s->l[s->i] || !s->l[s->i + 1]
		|| ft_ism(s->l[s->i + 1]) || ft_iss(s->l[s->i + 1]))
	{
		s->nb++;
		if (s->l[s->i])
			s->i++;
		return (1);
	}
	if (s->l[s->i])
		s->i++;
	return (0);
}

void	ft_iplus(t_shell *s, int ver)
{
	if (ver == 1)
	{
		s->i++;
		s->k++;
	}
	else if (ver == 2)
	{
		s->i += 2;
		s->k += 2;
	}
	s->nb++;
}
