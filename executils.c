/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:53:51 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:53:53 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setcmd2(t_shell *s)
{
	char	**paths;
	char	*pth;

	pth = ft_getenv(s->env, "PATH");
	paths = ft_split(pth, ':');
	free(pth);
	s->nb = 0;
	while (paths && paths[s->nb] && s->t[s->i].tok[0])
	{
		pth = ft_join(paths[s->nb], s->t[s->i].tok);
		if (access(pth, F_OK) == 0)
		{
			s->t[s->i].cmd = pth;
			ft_free(paths);
			return (1);
		}
		s->nb++;
		free(pth);
	}
	ft_free(paths);
	printf("%s: command not found\n", s->t[s->i].tok);
	s->exit = 127;
	return (0);
}

int	ft_setcmd(t_shell *s)
{
	if (ft_isdir(s->t[s->i].tok))
	{
		printf ("%s: Is a directory\n", s->t[s->i].tok);
		s->exit = 126;
	}
	else if (ft_islash(s->t[s->i].tok) && access(s->t[s->i].tok, F_OK) != 0)
	{
		printf ("%s: No such file or directory\n", s->t[s->i].tok);
		s->exit = 127;
	}
	else if (ft_isbuiltin(s, 0) == 1 || ft_isbuiltin2(s, 0) == 1)
	{
		s->t[s->i].cmd = ft_strcpy(s->t[s->i].tok);
		return (1);
	}
	else if (access(s->t[s->i].tok, F_OK) == 0)
	{
		s->t[s->i].cmd = ft_strcpy(s->t[s->i].tok);
		return (1);
	}
	else if (access(s->t[s->i].tok, F_OK) != 0)
		return (ft_setcmd2(s));
	return (0);
}

void	ft_setarg2(t_shell *s)
{
	int	i;
	int	k;

	k = 1;
	i = s->i + 1;
	while (s->t[i].tok && s->t[i].type != 3)
	{
		if (s->t[i].tok && s->t[i].type == 2)
			s->t[s->i].arg[k++] = ft_strcpy(s->t[i].tok);
		i++;
	}
}

void	ft_setarg(t_shell *s)
{
	int	i;
	int	k;

	i = s->i + 1;
	k = 0;
	while (s->t[i].tok && s->t[i].type != 3)
	{
		if (s->t[i].tok && s->t[i].type == 2)
			k++;
		i++;
	}
	s->t[s->i].arg = ft_calloc(sizeof(char *), k + 2);
	s->t[s->i].arg[0] = ft_strcpy(s->t[s->i].cmd);
	if (k == 0)
	{
		s->t[s->i].arg[1] = 0;
		return ;
	}
	ft_setarg2(s);
}

void	ft_writein(t_shell *s, int hdpip[])
{
	int	i;

	i = 0;
	while (s->t[s->i].here && s->t[s->i].here[i])
	{
		write(hdpip[1], &s->t[s->i].here[i], 1);
		i++;
	}
}
