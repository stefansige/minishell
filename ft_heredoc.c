/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:47:10 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 14:47:12 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sethere(t_shell *s, char *buf)
{
	s->nb = s->i - 1;
	while (s->nb >= 0 && s->t[s->nb].type != 3)
	{
		if (s->t[s->nb].type == 1)
		{
			s->t[s->nb].here = buf;
			s->t[s->nb].input = -5;
			return ;
		}
		s->nb--;
	}
}

void	ft_heredoc(t_shell *s)
{
	char	*line;
	char	*buf;
	char	*temp;

	buf = NULL;
	while (1)
	{
		line = get_next_line(s.)
		if (!line)
		{
			printf("warning heredocument delimited by end of file\n");
			return ;
		}
		if (ft_compare(s->t[s->i + 1].tok, line))
		{
			free (line);
			ft_sethere(s, buf);
			return ;
		}
		temp = ft_strcpy(buf);
		if (buf)
			free (buf);
		buf = ft_strjoin(temp, line);
		if (temp)
			free (temp);
		free(line);
	}
	if (g_exit != 0)
	{
		s->exit = g_exit;
		g_exit = 0;
	}
}
