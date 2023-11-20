/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexorutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:08:18 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 17:08:20 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lnull(t_shell *s)
{
	s->t[s->nb - 1].cmd = NULL;
	s->t[s->nb - 1].input = -1;
	s->t[s->nb - 1].output = -1;
	s->t[s->nb - 1].here = NULL;
	s->t[s->nb - 1].arg = NULL;
	s->t[s->nb - 1].type = 0;
}

void	ft_lalloc(t_shell *s, int fun, int ver)
{
	if (fun == 1)
		ft_iplus(s, ver);
	else if (fun == 2)
	{
		if (ft_qplus(s, s->l[s->i]) == 0)
			return ;
	}
	s->t[s->nb - 1].tok = ft_calloc(sizeof(char), s->k + 1);
	s->k = 0;
	ft_lnull(s);
}

void	ft_lsettype(t_shell *s, int ver)
{
	if (ver == 1)
	{
		if (s->l[s->i] == '|')
			s->t[s->nb].type = 3;
		if (s->l[s->i] == '>')
			s->t[s->nb].type = 4;
		if (s->l[s->i] == '<')
			s->t[s->nb].type = 5;
	}
	else if (ver == 2)
	{
		if (s->l[s->i] == '>')
			s->t[s->nb].type = 6;
		else
			s->t[s->nb].type = 7;
	}
}

void	ft_lset(t_shell *s, int fun, int ver)
{
	ft_lsettype(s, ver);
	if (fun == 1)
		ft_iplus(s, ver);
	while (s->ln < s->i)
		s->t[s->nb - 1].tok[s->y++] = s->l[s->ln++];
	s->y = 0;
	s->ln = s->i;
}
