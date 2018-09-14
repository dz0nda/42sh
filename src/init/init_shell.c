/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:58:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 23:16:40 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			init_shell(int ac, const char **av)
{
	char	*path;

	path = NULL;
	if (!(path = search_path_of_101sh(av[0])))
		return (EXIT_FAILURE);
	if (init_files(av[0]))
		return (EXIT_FAILURE);
	if (init_env(ac, av))
		return (EXIT_FAILURE);
	if (init_set(ac, av))
		return (EXIT_FAILURE);
	if (init_builtins((const char *)path))
		return (EXIT_FAILURE);
	ft_strdel(&path);
	return (EXIT_SUCCESS);
}
