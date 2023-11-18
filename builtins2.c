/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:28:20 by snovakov          #+#    #+#             */
/*   Updated: 2023/11/18 19:28:22 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **arg)
{
	bool	flag;
	int		i;

	flag = true;
	i = 1;
	if (ft_compare(arg[i], "-n"))
	{
		flag = false;
		i++;
	}
	while (arg[i])
	{
		if (arg[i + 1])
			printf("%s ", arg[i]);
		else
			printf("%s", arg[i]);
		i++;
	}
	if (flag)
		printf("\n");
}

void	ft_export_forth(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
}

void	ft_pwd(char **arg, char **env)
{
	char	*pwd;

	(void)arg;
	(void)env;
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	if (pwd)
		free(pwd);
}

int	ft_getenv_n(char **env, char *s)
{
	unsigned int	i;
	int	j;

	i = 0;
	j = 0;
	while (s && s[i] && env[j] && env[j][i])
	{
		if (env[j][i] != s[i])
		{
			i = 0;
			j++;
		}
		else
			i++;
	}
	if (!env[j] || !s || i != ft_strlen(s))
		return (0);
	return (j);
}

char	*ft_rereset(char *varn, char *varc)
{
	char	*re;
	int		i;
	int		j;

	i = 0;
	j = 0;
	re = NULL;
	re = (char *)ft_calloc(sizeof(char), (ft_strlen(varn) + ft_strlen(varc) + 2));
	while (varn && varn[i])
	{
		re[i] = varn[i];
		i++;
	}
	re[i++] = '=';
	while (varc && varc[j])
	{
		re[i] = varc[j];
		i++;
		j++;
	}
	re[i] = '\0';
	return (re);
}

void	ft_reset(char **env, char *varn, char *varc)
{
	int	p;

	p = ft_getenv_n(env, varn);
	free(env[p]);
	env[p] = ft_rereset(varn, varc);
}

void	ft_unset_real(char *arg, char **env)
{
	char	**new_env;
	int		i;
	int		p;

	i = 0;
	while (env[i])
		i++;
	p = ft_getenv_n(env, arg);
	free(env[p]);
	new_env = ft_calloc(sizeof(char *), i);
	i = 0;
	while (++i < p)
		new_env[i] = env[i];
	while (env[++i])
		new_env[i - 1] = env[i];
	ft_free(env);
	env = new_env;
}

void	ft_set_cd(char **env)
{
	char	*oldpwd;

	oldpwd = ft_getenv(env, "PWD");
	if (ft_getenv(env, "OLDPWD"))
	{
		if (oldpwd)
			ft_reset(env, "OLDPWD", oldpwd);
		else
			ft_unset_real(oldpwd, env);
	}
	if (oldpwd)
		ft_reset(env, "PWD", getcwd(NULL, 0));
}

void	ft_cd(char **arg, char **env)
{
	if (arg[2])
		printf("cd: too many arguments");
	else
	{
		if (ft_isdir(arg[1]))
		{
			chdir(arg[1]);
			ft_set_cd(env);
		}
		else
			printf("cd: %s: No such file or directory", arg[1]);
	}
}