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

int	g_exit = 0;

void	signal_ctrlc(int signum)
{
	(void)signum;
	printf("\n");
	g_exit = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_minishell(t_shell *s)
{
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_ctrlc);
		s->l = readline(s->prompt);
		if (g_exit != 0)
		{
			s->exit = g_exit;
			g_exit = 0;
		}
		if (s->l)
		{
			if (ft_valid(s->l))
				if (ft_lexor(s))
					if (ft_token(s))
						ft_exec(s);
		}
		else
			ft_exit(s, 1);
		ft_restart(s);
	}
}

char	**ft_dpcpy(char **s)
{
	int		i;
	int		y;
	char	**ret;

	ret = ft_calloc(sizeof(char *), ft_dpstrlen(s) + 1);
	i = 0;
	while (s && s[i])
	{
		ret[i] = ft_calloc(sizeof(char), ft_strlen(s[i]) + 1);
		i++;
	}
	i = 0;
	while (s && s[i])
	{
		y = 0;
		while (s[i][y])
		{
			ret[i][y] = s[i][y];
			y++;
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_init(t_shell *s, char **env)
{
	char	*tmp;

	s->prompt = ft_strcpy("\033[1;31mminishell>\033[0m");
	s->exit = 0;
	s->env = ft_dpcpy(env);
	tmp = getcwd(NULL, 0);
	ft_reset(s->env, "SHELL", tmp);
	if (tmp)
		free(tmp);
	s->ln = 0;
	s->l = NULL;
	s->tnb = 0;
	s->t = NULL;
	s->i = 0;
	s->nb = 0;
	g_exit = 0;
	s->import = dup(STDIN_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	s;

	(void)argc;
	(void)argv;
	ft_init(&s, env);
	ft_minishell(&s);
}
