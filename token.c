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

int	ft_setoutput(t_shell *s, int ver)
{
	s->nb = s->i - 1;
	while (s->nb >= 0 && s->t[s->nb].type != 3)
	{
		if (s->t[s->nb].type == 1)
		{
			if (ver == 1)
				s->t[s->nb].output = open(s->t[s->i + 1].tok, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				s->t[s->nb].output = open(s->t[s->i + 1].tok, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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

int	ft_checkred(t_shell *s)
{
	if (!s->t[s->i + 1].tok)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		s->exit = 2;
		return (1);
	}
	if (ft_isact(s->t[s->i + 1].type))
	{
		printf("bash: syntax error near unexpected token `%s'\n", s->t[s->i + 1].tok);
		s->exit = 2;
		return (1);
	}
	if (s->t[s->i + 1].type == 0)
	{
		s->t[s->i + 1].type = 10;
		if (s->t[s->i].type == 4 || s->t[s->i].type == 6)
		{
			if (access(s->t[s->i + 1].tok, F_OK) != 0)
				return (ft_setoutput(s, 0));
			else if (access(s->t[s->i + 1].tok, W_OK) != 0)
			{
				printf("bash: %s: Permission denied\n", s->t[s->i + 1].tok);
				s->exit = 1;
				ft_disable(s);
				return (0);
			}
			else if (s->t[s->i].type == 4)
				return (ft_setoutput(s, 0));
			else if (s->t[s->i].type == 6)
				return (ft_setoutput(s, 1));
		}
		else if (s->t[s->i].type == 5 || s->t[s->i].type == 7)
		{
			if (s->t[s->i].type == 7)
			{
				ft_heredoc(s);
				return (0);
			}
			if (access(s->t[s->i + 1].tok, R_OK) != 0)
			{
				printf("bash: %s: No such file or directory\n", s->t[s->i + 1].tok);
				s->exit = 1;
				ft_disable(s);
				return (0);
			}
			else if (access(s->t[s->i + 1].tok, R_OK) != 0)
			{
				printf("bash: %s: Permission denied\n", s->t[s->i + 1].tok);
				s->exit = 1;
				ft_disable(s);
				return (0);
			}
			return (ft_setinput(s));
		}
	}
	return (0);
}

int	ft_checkpipe(t_shell *s)
{
	if (s->i == 0 || s->t[s->i + 1].type == 3)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		s->exit = 2;
		return (1);
	}
	else if (!s->t[s->i + 1].tok)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		s->exit = 2;
		return (1);
	}
	s->i++;
	return (0);
}

int	ft_token(t_shell *s)
{
	s->i = 0;
	while (s->t[s->i].tok)
	{
		if (s->t[s->i].type == 0 && (s->i == 0 || s->t[s->i - 1].type == 3))
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
