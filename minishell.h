/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:59:58 by snovakov          #+#    #+#             */
/*   Updated: 2023/10/04 17:00:00 by snovakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct s_token
{
	char	*tok;
	char	*cmd;
	char	**arg;
	char	*here;
	int		input;
	int		output;
	int		type;		// 1-cmd, 2-arg, 3-pipe, 4-rred, 5-lred, 6-rapp, 7-lapp, 8-singleQ 9-doubleQ 10-file
}	t_token;

typedef struct s_shell
{
	char			**env;
	t_token			*t;
	int				tnb;
	int				i;
	unsigned int	exit;
	int				nb;
	int				ln;
	int				import;
	char			*l;
	char			*prompt;
}	t_shell;

void			*ft_calloc(size_t size, size_t count);
unsigned int	ft_strlen(char *s);
void			ft_dollar(t_shell *s);
int				ft_isvname(char c);
unsigned int	ft_dolen(char *s, int start);
char			*ft_getenv(char **env, char *s);
int				ft_token(t_shell *s);
char			*ft_join(char *str1, char *str2);
int				ft_perror(t_shell *s);
int				ft_berror(t_shell *s);
char			*ft_strcpy(char *s);
char			**ft_split(char *s, char c);
void			ft_exec(t_shell *s);
void			ft_free(char **s);
int				ft_isbuiltin(t_shell *s, int ver);
int				ft_compare(char *s1, char *s2);
void			ft_heredoc(t_shell *s);
char			*ft_strjoin(char *s1, char *s2);
int				ft_isarg(int i);
int				ft_atoi(const char *nptr);
int				ft_isdir(char *s);
void			ft_echo(char **arg, char **env);
void			ft_pwd(char **arg, char **env);
void			ft_env(char **arg, char **env);

#endif
