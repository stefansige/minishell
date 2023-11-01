/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:17:12 by snovakov          #+#    #+#             */
/*   Updated: 2023/10/04 14:17:14 by snovakov         ###   ########.fr       */
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
			free (line);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_iplus(t_shell *s, int ver)
{
	if (ver == 1)
		s->i++;
	else if (ver == 2)
		s->i += 2;
	s->nb++;
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
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

void	ft_qplus(t_shell *s, int ver, char *l)
{
	s->nb++;
	s->i++;
	if (ver == 1)
		while (l[s->i] && l[s->i] != '\'')
			s->i++;
	else if (ver == 2)
		while (l[s->i] && l[s->i] != '\"')
			s->i++;
	s->i++;
}

void	ft_tcount(t_shell *s, char *l)
{
	s->i = 0;
	s->nb = 0;
	while (l[s->i])
	{
		if(ft_iss(l[s->i]))
			s->i++;
		else if ((!ft_ism(l[s->i]) && ft_iss(l[s->i + 1])) ||
			(!ft_ism(l[s->i]) && l[s->i + 1] == '\0') ||
			(ft_ism(l[s->i + 1]) && !ft_ism(l[s->i])))
				ft_iplus(s, 1);
		else if (l[s->i] == '|' || l[s->i] == '>' || l[s->i] == '<')
			ft_iplus(s, 1);
		else if ((l[s->i] == '>' && l[s->i + 1] == '>') || (l[s->i] == '<' && l[s->i + 1] == '<'))
			ft_iplus(s, 2);
		else if (l[s->i] == '\'')
			ft_qplus(s, 1, l);
		else if (l[s->i] == '\"')
			ft_qplus(s, 2, l);
		else
			s->i++;
	}
	s->tnb = s->nb;
}

void	ft_lalloc(t_shell *s, int fun, int ver, char *l)
{
	int	y;
	int	k;

	if (fun == 1)
		ft_iplus(s, ver);
	else if (fun == 2)
		ft_qplus(s, ver, l);
	k = 0;
	y = s->ln;
	while (y < s->i)
	{
		k++;
		y++;
	}
	s->t[s->nb - 1].tok = ft_calloc(k + 1 , (sizeof(char)));
	s->t[s->nb - 1].cmd = NULL;
	s->t[s->nb - 1].input = -1;
	s->t[s->nb - 1].output = -1;
	s->ln = s->i;
}

void	ft_tlen(t_shell *s, char *l)
{
	s->i = 0;
	s->nb = 0;
	s->ln = 0;
	while (l[s->i])
	{
		if(ft_iss(l[s->i]))
		{
			s->ln++;
			s->i++;
		}
		else if ((!ft_ism(l[s->i]) && ft_iss(l[s->i + 1])) ||
			(!ft_ism(l[s->i]) && l[s->i + 1] == '\0') ||
			(ft_ism(l[s->i + 1]) && !ft_ism(l[s->i])))
				ft_lalloc(s, 1, 1, l);
		else if (l[s->i] == '|' || l[s->i] == '>' || l[s->i] == '<')
			ft_lalloc(s, 1, 1, l);
		else if ((l[s->i] == '>' && l[s->i + 1] == '>') || (l[s->i] == '<' && l[s->i + 1] == '<'))
			ft_lalloc(s, 1, 2, l);
		else if (l[s->i] == '\'')
			ft_lalloc(s, 2, 1, l);
		else if (l[s->i] == '\"')
			ft_lalloc(s, 2, 2, l);
		else
			s->i++;
	}
}

void	ft_lsettype(t_shell *s, int fun, int ver)
{
	if (fun == 1 && ver == 1)
	{
		if (s->l[s->i] == '|')
			s->t[s->nb].type = 3;
		if (s->l[s->i] == '>')
			s->t[s->nb].type = 4;
		if (s->l[s->i] == '<')
			s->t[s->nb].type = 5;
	}
	else if (fun == 1 && ver == 2)
	{
		if (s->l[s->i] == '>')
			s->t[s->nb].type = 6;
		else
			s->t[s->nb].type = 7;
	}
	else if (fun == 2 && ver == 1)
		s->t[s->nb].type = 8;
	else if (fun == 2 && ver == 2)
		s->t[s->nb].type = 9;
	else
		s->t[s->nb].type = 0;
}

void	ft_lset(t_shell *s, int fun, int ver, char *l)
{
	int	y;
	int	k;

	ft_lsettype(s, fun, ver);
	if (fun <= 1)
		ft_iplus(s, ver);
	else if (fun == 2)
		ft_qplus(s, ver, l);
	y = s->ln;
	k = 0;
	while (y < s->i)
		s->t[s->nb - 1].tok[k++] = l[y++];
 	s->ln = s->i;
}

void	ft_tset(t_shell *s, char *l)
{
	s->i = 0;
	s->nb = 0;
	s->ln = 0;
	while (l[s->i])
	{
		if(ft_iss(l[s->i]))
		{
			s->ln++;
			s->i++;
		}
		else if ((!ft_ism(l[s->i]) && ft_iss(l[s->i + 1])) ||
			(!ft_ism(l[s->i]) && l[s->i + 1] == '\0') ||
			(ft_ism(l[s->i + 1]) && !ft_ism(l[s->i])))
				ft_lset(s, 0, 1, l);
		else if (l[s->i] == '|' || l[s->i] == '>' || l[s->i] == '<')
			ft_lset(s, 1, 1, l);
		else if ((l[s->i] == '>' && l[s->i + 1] == '>') || (l[s->i] == '<' && l[s->i + 1] == '<'))
			ft_lset(s, 1, 2, l);
		else if (l[s->i] == '\'')
			ft_lset(s, 2, 1, l);
		else if (l[s->i] == '\"')
			ft_lset(s, 2, 2, l);
		else
			s->i++;
	}
}

int	ft_lexor(t_shell *s)
{
	ft_dollar(s);
	ft_tcount(s, s->l);
	s->t = (t_token*)malloc(sizeof(t_token) * (s->tnb + 1));
	s->t[s->tnb].tok = NULL;
	ft_tlen(s, s->l);
	ft_tset(s, s->l);
	return (1);
}

void	ft_minishell(t_shell *s)
{
	while (1)
	{
		s->l = readline(s->prompt);
		if (s->l)
			if (ft_valid(s->l))
				if (ft_lexor(s))
					if (ft_token(s))
						ft_exec(s);
		free(s->l);
	}
}

char	**ft_dpcpy(char **s)
{
	int	i;
	int	y;
	char	**ret;

	i = 0;
	while (s[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (s[i])
	{
		ret[i] = ft_calloc(ft_strlen(s[i]) + 1, sizeof(char));
		i++;
	}
	i = 0;
	while (s[i])
	{
		y = 0;
		while (s[i][y])
		{
			ret[i][y] = s[i][y];
			y++;
		}
		i++;
	}
	return (ret);
}

void	ft_init(t_shell *s, char **env)
{
	s->prompt = "\nstefko=>";
	s->env = ft_dpcpy(env);
	s->ln = 0;
	s->tnb = 0;
	s->i = 0;
	s->nb = 0;
	s->import = dup(STDIN_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_shell s;

	(void)argc;
	(void)argv;
	ft_init(&s, env);
	ft_minishell(&s);
}
