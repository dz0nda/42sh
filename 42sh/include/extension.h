/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:16:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 06:20:11 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXTENSION_H
# define EXTENSION_H

#include "./parsing.h"
#include "./execute.h"
#include "./stdin.h"

int			extension(t_seq **b_seq);
char		**ft_split_bquote(const char *str, char *to_split);
int			ft_dollar(char **cmd, int *j);
int			ft_manage_quote(char ***tablo, int i, int *j, char* (*f)(char*, int*));
char		*ft_replace_quote(char *str, int *j);
char		*ft_replace_dquote(char *str, int *j);
int			extension_error(t_seq **b_seq);
int			bquote_manager(char ***cmd, int *j_index, int *i_index, int bquote);
int			backslash_manager(char ***cmd, int i, int *j, int d_quote);

#endif