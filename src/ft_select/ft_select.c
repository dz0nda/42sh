/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 07:53:43 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_select(t_editor **ed, int version)
{
	if ((*ed)->t.elem)
	{
		version == 0 ? ft_init_select(ed) : 0;
		if ((*ed)->sel->bp < (*ed)->sel->ws.ws_col)
		{
			if ((*ed)->t.elem[1])
			{
				version == 0 ? ft_print_params((*ed)->sel) : 0;
				(*ed)->tabu = 0;
			}
			else if ((*ed)->t.elem[0] && (*ed)->tabu == -1)
					replace_line_after_tab(ed);
			ft_manage_touch(ed, version);
		}
		else
		{
			ft_free_t_tab(&(*ed)->t);
			ft_free_t_select(&(*ed)->sel);
			(*ed)->tabu = -1;
			ft_putchar('\a');
		}
	}
	return (0);
}
