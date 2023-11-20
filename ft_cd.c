/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:39:31 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/20 16:39:32 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset(char **env, char *varn, char *varc)
{
	int		p;

	p = ft_getenv_n(env, varn);
	free(env[p]);
	env[p] = ft_rereset(varn, varc);
}

void	ft_unset_real(t_shell *s, char *arg)
{
	char	**new_env;
	int		i;
	int		p;

	i = 0;
	while (s->env[i])
		i++;
	p = ft_getenv_n(s->env, arg);
	new_env = ft_calloc(sizeof(char *), i);
	i = 0;
	while (i < p)
	{
		new_env[i] = s->env[i];
		i++;
	}
	free(s->env[i]);
	i++;
	while (s->env[i])
	{
		new_env[i - 1] = s->env[i];
		i++;
	}
	free(s->env);
	s->env = new_env;
}

void	ft_set_cd(t_shell *s)
{
	char	*oldpwd;
	char	*newpwd;
	char	*tmp;

	oldpwd = ft_getenv(s->env, "PWD");
	newpwd = getcwd(NULL, 0);
	tmp = ft_getenv(s->env, "OLDPWD");
	if (tmp)
	{
		free(tmp);
		if (oldpwd)
			ft_reset(s->env, "OLDPWD", oldpwd);
		else
			ft_unset_real(s, "OLDPWD");
	}
	if (oldpwd)
		ft_reset(s->env, "PWD", newpwd);
	if (oldpwd)
		free(oldpwd);
	if (newpwd)
		free(newpwd);
}

void	ft_emptycd(t_shell *s)
{
	char	*tmp2;

	tmp2 = ft_getenv(s->env, "HOME");
	if (tmp2)
	{
		chdir(tmp2);
		ft_set_cd(s);
	}
	if (tmp2)
		free(tmp2);
}

void	ft_cd(t_shell *s)
{
	s->exit = 0;
	if (!s->t[s->i].arg[1])
		ft_emptycd(s);
	else if (!s->t[s->i].arg[1][0])
		return ;
	else if (s->t[s->i].arg[2])
	{
		printf("cd: too many arguments");
		s->exit = 1;
	}
	else
	{
		if (ft_isdir(s->t[s->i].arg[1]))
		{
			chdir(s->t[s->i].arg[1]);
			ft_set_cd(s);
		}
		else
		{
			printf("cd: %s: No such file or directory\n", s->t[s->i].arg[1]);
			s->exit = 1;
		}
	}
}
