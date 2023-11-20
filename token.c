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

int	ft_checkinput(t_shell *s)
{
	if (s->t[s->i].type == 7)
	{
		ft_heredoc(s);
		return (0);
	}
	if (access(s->t[s->i + 1].tok, R_OK) != 0)
	{
		printf("%s: No such file or directory\n", s->t[s->i + 1].tok);
		s->exit = 1;
		ft_disable(s);
		return (0);
	}
	else if (access(s->t[s->i + 1].tok, R_OK) != 0)
	{
		printf("%s: Permission denied\n", s->t[s->i + 1].tok);
		s->exit = 1;
		ft_disable(s);
		return (0);
	}
	return (ft_setinput(s));
}

int	ft_checkred(t_shell *s)
{
	if (!s->t[s->i + 1].tok)
	{
		printf("syntax error near unexpected token `newline'\n");
		s->exit = 2;
		return (1);
	}
	if (ft_isact(s->t[s->i + 1].type))
	{
		printf("syntax error near unexpected token `%s'\n", s->t[s->i + 1].tok);
		s->exit = 2;
		return (1);
	}
	if (s->t[s->i + 1].type == 0)
	{
		s->t[s->i + 1].type = 10;
		if (s->t[s->i].type == 4 || s->t[s->i].type == 6)
			return (ft_checkoutput(s));
		else if (s->t[s->i].type == 5 || s->t[s->i].type == 7)
			return (ft_checkinput(s));
	}
	return (0);
}

int	ft_checkpipe(t_shell *s)
{
	if (s->i == 0 || s->t[s->i + 1].type == 3)
	{
		printf("syntax error near unexpected token `|'\n");
		s->exit = 2;
		return (1);
	}
	else if (!s->t[s->i + 1].tok)
	{
		printf("syntax error near unexpected token `newline'\n");
		s->exit = 2;
		return (1);
	}
	s->i++;
	return (0);
}

int	ft_token2(t_shell *s)
{
	s->t[s->i].type = 1;
	s->i++;
	while (s->t[s->i].tok && s->t[s->i].type != 3)
	{
		if (s->t[s->i].type >= 4 && s->t[s->i].type <= 7)
		{
			if (ft_checkred(s))
				return (0);
			s->i += 2;
		}
		else
			s->t[s->i++].type = 2;
	}
	return (1);
}

int	ft_token(t_shell *s)
{
	s->i = 0;
	while (s->t[s->i].tok && g_exit == 0)
	{
		if (s->t[s->i].type == 0 && (s->i == 0 || s->t[s->i - 1].type == 3))
		{
			if (ft_token2(s) == 0)
				return (0);
		}
		else if (s->t[s->i].type >= 4 && s->t[s->i].type <= 7)
		{
			if (ft_checkred(s))
				return (0);
			s->i += 2;
		}
		else if (s->t[s->i].type == 3)
		{
			if (ft_checkpipe(s))
				return (0);
		}
		else
			s->i++;
	}
	return (1);
}
