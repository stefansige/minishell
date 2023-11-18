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

void	ft_echo(char **arg, char **env)
{
	bool	flag;
	int		i;

	(void)env;
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