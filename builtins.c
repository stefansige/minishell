/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azennari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:27 by azennari          #+#    #+#             */
/*   Updated: 2023/11/16 19:09:20 by azennari         ###   ########.fr       */
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

void	ft_set_cd(char **env)
{
	char	*oldpwd;

	oldpwd = ft_getenv(env, "PWD");
	if (ft_getenv(env, "OLDPWD"))
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

void	ft_export_arg_len(char *arg, int *nlen, int *clen)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	nlen[0] = i;
	while (arg[i])
		i++;
	clen[0] = i - nlen[0] - 1;
}

void	ft_read_export_arg(char *arg, char *varn, char *varc)
{
	int	i;
	int	nlen;
	int	clen;

	i = 0;
	ft_export_arg_len(arg, &nlen, &clen);
	varn = (char *)ft_calloc(sizeof(char), nlen + 1);
	varc = (char *)ft_calloc(sizeof(char), clen + 1);
	while (i <= nlen)
	{
		varn[i] = arg[i];
		i++;
	}
	i = 0;
	while ((i + nlen + 1) <= clen)
	{
		varc[i] = arg[i + nlen + 1];
		i++;
	}
}

void	ft_set(char **env, char *varn, char *varc)
{
	char	**new_env;
	int		envlen;

	envlen = 0;
	while (env[envlen])
		envlen++;
	//Allocate a new env, copy everthing inside it and add the new var
	//Free the old env, then replace it with the already allocated and fresh new env
}

void	ft_export(char **arg, char **env)
{
	int		i;
	char	*varn;
	char	*varc;

	i = -1;
	while (arg[++i])
	{
		ft_read_export_arg(arg[i], varn, varc);
		if (ft_getenv(env, varn) && varc)
			ft_reset(env, varn, varc);
		else if (varc)
			ft_set(env, varn, varc);
		free(varn);
		free(varc);
	}
}

void	ft_unset(char **arg, char **env)
{
	//Find the varn (variable name), then use ft_getenv_n to locate it
	//Allocate memory for a new_env, then copy everything in two steps, one before and one after the var to unset
	//Free the old one and replace it with the new one
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
