/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azennari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:53:27 by azennari          #+#    #+#             */
/*   Updated: 2023/11/13 18:10:10 by azennari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_cd(char *arg, char **env)
{
	//The function chdir does most of the job, but doesn't do anything to env by itself
	//Need to change OLDPWD and PWD. This is where other functions comes in play
	//OLDPWD becomes as PWD was before the passage, then PWD becomes the new one. Not further record is kept, no oldoldpwd or change history
	//If PWD is unset, OLDPWD gets unset here. If OLDPWD is unset, is not reset, and PWD behaves regularly. If both are unset, nothing happens
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

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	ft_exit(void)
{
	//Even if seemingly the easiest, it can't simply be an exit as it has to not close the program when placed in a pipe
}