/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:39:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/13 03:47:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define HEREDOC 10
# define NOTHING -1
#include "./parsing.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "./stdin.h"

char			**g_bin;

int				ft_solver(t_op *tmp_exec, int fd);
char			*ft_search_bin(char *cmd);
char			*ft_go_to(char *bin, int nb);
void			ft_skip(char **ttab);
void			ft_get_bin();
int				ft_exec(t_op *tmp_op, char *bin_cmd);
int				ft_builtins(t_op *t_exec, int what, int flag);
int				ft_check_command(char *cmd);
void			ft_open_redirect(char *file, int flag, int flag2, int fd);
int				ft_return_flag(t_redirect *redirect);
int				ft_echo(t_op *t_exec, int flag);
int				ft_cd(t_op *t_exec, int flag);
int				ft_exit(t_op *t_exec, int flag);
int 			ft_open_redirect_builtins(char *file, int flag, int fd);
void			ft_heredoc(t_redirect *redirect, char *bin, int flag);
int				ft_redirect_heredoc(t_redirect *redirect, int flag, char *bin, pid_t pid);
int				ft_check_direct_command(char *cmd);
int				ft_check_file_is_directory(char *file);
int				ft_check_source(char *source);
int				ft_return_flag2(t_op *op);
int				ft_return_fd(t_op *t_exec, int flag);
int				ft_while_redirect(t_redirect *redirect, char *bin_cmd, pid_t cpid, int built, char **cmd, t_op *op);
#endif
