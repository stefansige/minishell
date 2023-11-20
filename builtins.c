/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azennari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:27 by azennari          #+#    #+#             */
/*   Updated: 2023/11/18 20:08:45 by azennari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **arg)
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
	return (0);
}

int	ft_export_forth(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
	return (0);
}

int	ft_pwd(char **arg, char **env)
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
	return (0);
}
