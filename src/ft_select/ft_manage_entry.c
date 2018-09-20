/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_entry.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/27 13:29:05 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 14:17:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

int		ft_manage_entry(char **entry, t_select **sel)
{
	int		ret;

	ret = 1;
	(*entry) = ft_read_entry(&(*sel));
	if ((*entry)[0] != -1)
		ret = ft_manage_touch(&(*entry), &(*sel));
	return (ret);
}
