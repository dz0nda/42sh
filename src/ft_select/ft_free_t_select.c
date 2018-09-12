/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_t_select.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/29 03:42:33 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:09:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_free_t_select(t_select **t)
{
	t_line		*tmp;

	if (!(*t))
		return (0);
	if (!(*t)->line)
	{
		free((*t));
		return (0);
	}
	while ((*t)->line)
	{
		tmp = (*t)->line;
		(*t)->line = (*t)->line->next;
		if (tmp->elem)
			ft_strdel(&tmp->elem);
		free(tmp);
		tmp = NULL;
	}
	free(*(t));
	return (0);
}
