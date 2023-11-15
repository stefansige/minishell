/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azennari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:27 by azennari          #+#    #+#             */
/*   Updated: 2023/11/15 19:00:51 by azennari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **arg, char **env)
{
	bool	flag;
	int		i;

	(void)env;
	flag = false;
	i = 0;
	if (!(strcmp(*arg[i], "-n")))
	{
		flag = true;
		i++;
	}
	while (*arg[i])
	{
		if (*arg[i + 1])
			printf("%s ", *arg[i]);
		else
			printf("%s", *arg[i]);
	}
	if (flag)
		printf("\n");
}

void	ft_pwd(char **arg, char **env)
{
	char	*pwd;

	void(arg);
	void(env);
	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

int	ft_getenv_n(char **env, char *s)
{
	int	i;
	int	j;

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
		return (NULL);
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
	re = ft_calloc(sizeof(char), (ft_strlen(varn) + ft_strlen(varc) + 2));
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

void	ft_set_cd(char **env)
{
	char	*oldpwd;

	oldpwd = ft_getenv("PWD");
	if (ft_getenv("OLDPWD"))
	{
		if (oldpwd)
			ft_reset(env, "OLDPWD", oldpwd);
		else
			//unset oldpwd
	}
	if (oldpwd)
		ft_reset(env, "PWD", getcwd(NULL, 0));
}

void	ft_cd(char **arg, char **env)
{
	if (arg[1])
		printf("cd: too many arguments");
	else
	{
		if (ft_isdir(arg[i]))
		{
			chdir(arg[i]);
			ft_set_cd(env);
		}
		else
			printf("cd: %s: No such file or directory", *arg[0]);
	}
}

void	ft_export(char **arg, char **env)
{
	//Necessary to realloc env and provide it with the new vars
	//Maybe use some existing reallocating funcs, either default or some coded here
	//Still in the "change the env" family. May use some common subfunctions
	//Planning the subfunctions early and make them small and well subdivided should save us work
	//Required a var finder to locate eventual already existing var with same name and replace it. Still have to reallocate though
}

void	ft_unset(char **arg, char **env)
{
	//Necessary to realloc env once found and scrapped the args
	//Still in the "change the env" family. May use some common subfunctions
	//Planning the subfunctions early and make them small and well subdivided should save us work
	//No need to use options, so no discrimination about the nature of the unset content
	//If it messes up when misused it's not a problem, as the original unset can really mess up stuff too
}

void	ft_env(char **arg, char **env)
{
	int	i;

	(void)arg;
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	ft_exit(void)
{
	//Even if seemingly the easiest, it can't simply be an exit as it has to not close the program when placed in a pipe
}
