/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azennari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:27 by azennari          #+#    #+#             */
/*   Updated: 2023/11/09 18:50:20 by azennari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

void	ft_echo(char **arg)
{
	bool	flag;
	int		i;

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

void	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}
