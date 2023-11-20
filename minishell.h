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
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <stddef.h>
# include <stdbool.h>
# include <signal.h>

extern int	g_exit;

typedef struct s_token
{
	char	*tok;
	char	*cmd;
	char	**arg;
	char	*here;
	int		input;
	int		output;
	int		type;
}	t_token;
// 1-cmd, 2-arg, 3-pipe, 4-rred, 5-lred, 6-rapp, 7-lapp, 10-file
typedef struct s_shell
{
	char			**env;
	t_token			*t;
	int				tnb;
	int				i;
	unsigned int	exit;
	int				nb;
	int				ln;
	int				k;
	int				y;
	int				flag;
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
int				ft_echo(char **arg);
int				ft_pwd(char **arg, char **env);
int				ft_env(char **arg, char **env);
int				ft_isbuiltin2(t_shell *s, int ver);
int				ft_strcmp(char *s1, char *s2);
int				ft_export_forth(char **env);
void			ft_cd(t_shell *s);
void			ft_reset(char **env, char *varn, char *varc);
void			ft_unset(t_shell *s);
char			**ft_dpcpy(char **s);
void			ft_export(t_shell *s);
void			ft_exit(t_shell *s, int ver);
void			ft_restart(t_shell *s);
void			ft_restart2(t_shell *s);
int				ft_valid(char *line);
void			signal_ctrlc(int signum);
size_t			ft_strlen(char *a);
char			*ft_strchr(char *a, char c);
char			*ft_strjoin(char *a, char *b);
char			*ft_surplus(char *buffer);
char			*ft_line(char *buffer);
char			*ft_read(int fd, char *res);
char			*get_next_line(int fd);

#endif
