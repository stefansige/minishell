/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:03:57 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 17:03:59 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_qset(t_shell *s, char c)
{
	if (s->i > 0 && !ft_iss(s->l[s->i - 1]) && !ft_ism(s->l[s->i - 1]))
	{
		while (s->ln < s->i)
			s->t[s->nb].tok[s->y++] = s->l[s->ln++];
	}
	s->i++;
	while (s->l[s->i] && s->l[s->i] != c)
		s->t[s->nb].tok[s->y++] = s->l[s->i++];
	if (!s->l[s->i] || !s->l[s->i + 1] || ft_ism(s->l[s->i + 1])
		|| ft_iss(s->l[s->i + 1]))
	{
		s->nb++;
		if (s->l[s->i])
			s->i++;
		s->y = 0;
		s->ln = s->i;
		return (1);
	}
	if (s->l[s->i])
		s->i++;
	s->ln = s->i;
	return (0);
}

void	ft_tcount(t_shell *s, char *l)
{
	s->i = 0;
	s->nb = 0;
	s->k = 0;
	while (l[s->i])
	{
		if (ft_iss(l[s->i]))
			s->i++;
		else if (l[s->i] == '\'' || l[s->i] == '\"')
			ft_qplus(s, l[s->i]);
		else if ((!ft_ism(l[s->i]) && ft_iss(l[s->i + 1]))
			|| (!ft_ism(l[s->i]) && l[s->i + 1] == '\0')
			|| (ft_ism(l[s->i + 1]) && !ft_ism(l[s->i])))
			ft_iplus(s, 1);
		else if ((l[s->i] == '>' && l[s->i + 1] == '>')
			|| (l[s->i] == '<' && l[s->i + 1] == '<'))
			ft_iplus(s, 2);
		else if (l[s->i] == '|' || l[s->i] == '>' || l[s->i] == '<')
			ft_iplus(s, 1);
		else
			s->i++;
	}
	s->tnb = s->nb;
}

void	ft_tlen(t_shell *s, char *l)
{
	s->i = 0;
	s->nb = 0;
	s->k = 0;
	while (l[s->i])
	{
		if (ft_iss(l[s->i]))
			s->i++;
		else if (l[s->i] == '\'' || l[s->i] == '\"')
			ft_lalloc(s, 2, 0);
		else if ((!ft_ism(l[s->i]) && ft_iss(l[s->i + 1]))
			|| (!ft_ism(l[s->i]) && l[s->i + 1] == '\0')
			|| (ft_ism(l[s->i + 1]) && !ft_ism(l[s->i])))
			ft_lalloc(s, 1, 1);
		else if ((l[s->i] == '>' && l[s->i + 1] == '>')
			|| (l[s->i] == '<' && l[s->i + 1] == '<'))
			ft_lalloc(s, 1, 2);
		else if (l[s->i] == '|' || l[s->i] == '>' || l[s->i] == '<')
			ft_lalloc(s, 1, 1);
		else
		{
			s->i++;
			s->k++;
		}
	}
}

void	ft_tset(t_shell *s, char *l)
{
	s->y = 0;
	s->i = 0;
	s->nb = 0;
	s->ln = 0;
	while (l[s->i])
	{
		if (ft_iss(l[s->i]))
		{
			s->ln++;
			s->i++;
		}
		else if (l[s->i] == '\'' || l[s->i] == '\"')
			ft_qset(s, l[s->i]);
		else if ((!ft_ism(l[s->i]) && ft_iss(l[s->i + 1]))
			|| (!ft_ism(l[s->i]) && l[s->i + 1] == '\0')
			|| (ft_ism(l[s->i + 1]) && !ft_ism(l[s->i])))
			ft_lset(s, 1, 1);
		else if ((l[s->i] == '>' && l[s->i + 1] == '>')
			|| (l[s->i] == '<' && l[s->i + 1] == '<'))
			ft_lset(s, 1, 2);
		else if (l[s->i] == '|' || l[s->i] == '>' || l[s->i] == '<')
			ft_lset(s, 1, 1);
		else
			s->i++;
	}
}

int	ft_lexor(t_shell *s)
{
	add_history(s->l);
	ft_dollar(s);
	ft_tcount(s, s->l);
	s->t = (t_token *)malloc(sizeof(t_token) * (s->tnb + 1));
	s->t[s->tnb].tok = NULL;
	ft_tlen(s, s->l);
	ft_tset(s, s->l);
	if (g_exit != 0)
	{
		s->exit = g_exit;
		g_exit = 0;
	}
	return (1);
}
