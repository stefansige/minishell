/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:11:42 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 17:11:44 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restart2(t_shell *s)
{
	if (s->t)
	{
		free(s->t);
		s->t = NULL;
	}
	if (s->l)
	{
		free(s->l);
		s->l = NULL;
	}
}

void	ft_restart(t_shell *s)
{
	int	i;

	i = 0;
	if (g_exit != 0)
	{
		s->exit = g_exit;
		g_exit = 0;
	}
	while (i < s->tnb && s->t)
	{
		if (s->t[i].tok)
			free(s->t[i].tok);
		if (s->t[i].cmd)
			free(s->t[i].cmd);
		if (s->t[i].arg)
			ft_free(s->t[i].arg);
		if (s->t[i].here)
			free(s->t[i].here);
		i++;
	}
	ft_restart2(s);
}

void	ft_exit(t_shell *s, int ver)
{
	ft_restart(s);
	ft_free(s->env);
	rl_clear_history();
	free (s->prompt);
	if (ver == 1)
	{
		if (g_exit != 0)
			exit (g_exit);
		else
			exit (s->exit);
	}
}

void	ft_checkexit2(t_shell *s)
{
	if (s->t[1].tok && s->t[1].type == 2)
		s->i = ft_atoi(s->t[1].tok);
	if (s->i == -1010101)
	{
		if (s->nb != -1)
			printf("exit\n");
		printf ("exit: %s: numeric argument required\n", s->t[1].tok);
		s->i = 2;
	}
	else if (s->t[1].tok && s->t[1].type == 2
		&& s->t[2].tok && s->t[2].type == 2)
	{
		if (s->nb != -1)
			printf("exit\n");
		printf ("exit: too many arguments\n");
		s->i = 1;
	}
	else if (s->nb != -1)
		printf("exit\n");
}

void	ft_checkexit(t_shell *s)
{
	if (ft_compare(s->t[0].tok, "exit") && s->t[0].type == 1)
	{
		s->t[0].type = -1;
		s->i = s->exit;
		s->nb = 0;
		while (s->t[s->nb].tok)
		{
			if (s->t[s->nb].type == 3)
			{
				s->nb = -1;
				break ;
			}
			s->nb++;
		}
		ft_checkexit2(s);
		if (s->nb != -1)
		{
			ft_exit(s, 0);
			exit (s->i);
		}
	}
}
