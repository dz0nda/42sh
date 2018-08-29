/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:16:23 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 04:43:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXTENSION_H
# define EXTENSION_H

#include "./parsing.h"
#include "./execute.h"
#include "./stdin.h"

typedef struct	s_bquote
{
	int			i;
	int			j;
	int			begin;
}				t_bquote;

int			extension(t_seq **b_seq);
char		**ft_split_bquote(const char *str, char *to_split);
int			ft_dollar(char ***cmd, int *i_index, int *j_index);
int			ft_manage_quote(char ***cmd, t_bquote **i, int *dquote);
//char		*ft_replace_quote(char *str, int *j);
//char		*ft_replace_dquote(char *str, int *j);
int			extension_error(t_seq **b_seq);
int			bquote_manager(char ***cmd, int *j_index, int *i_index, int bquote);
int			backslash_manager(char ***cmd, t_bquote **i, int d_quote);
void		ft_free_n_seq(t_seq **n_seq);
void		ft_free_n_op(t_op **n_op);
void		ft_free_n_redirect(t_redirect **n_redirect);
int			last_copy(char ***begin_copy, char **cmd, t_bquote *index, int ok);
void		search_index(char **begin_copy, int *i, int *j);
char		**first_copy(char **cmd, t_bquote *index, char *in_bquote, int *ok);
char		**search_prev(char **cmd, int i_max);
int			add_before_bquote(char *line, int begin, char ***cmd);
int			add_after_bquote(char *cmd, int j_index, char ***tablo, int ok);
int			manage_tild_and_dollars(char ***cmd, t_bquote **i);

#endif
