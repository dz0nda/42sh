/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/03 00:50:51 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 03:55:21 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

int		ft_count_line(t_select *t)
{
	int		pbl = ft_params_by_line(t);

	if (pbl == 0)
		return (1);
	return (ft_count_params(t->line) % ft_params_by_line(t) == 0 ?
	ft_count_params(t->line) / ft_params_by_line(t) :
	ft_count_params(t->line) / ft_params_by_line(t) + 1);
}
