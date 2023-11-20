/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:56:19 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:56:20 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lastcmd(t_shell *s)
{
	int	i;

	i = s->tnb - 1;
	while (i >= 0)
	{
		if (s->t[i].type == 1)
		{
			s->ln = i;
			return ;
		}
		i--;
	}
}

void	ft_permdenied(t_shell *s)
{
	printf("%s: Permission denied\n", s->t[s->i].tok);
	s->exit = 126;
}
