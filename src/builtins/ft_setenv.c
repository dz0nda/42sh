/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 04:13:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 18:31:54 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_setenv(const char *name, const char *value, int fd_open)
{
	char	*s;
	int		i;
	char	**env;

	s = NULL;
	i = -1;
	env = NULL;
	if (name == NULL)
		return (ft_env((t_op *) 0 , fd_open, 0));
	if (ft_strchr(name, '='))
		return (ft_bierrors("setenv", NULL, BIEQUAL, fd_open));
	if (!(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));
	else
	{
		while (g_env[++i])
			if ((ft_strcmp(g_env[i], s)) == 0)
				break ;
		ft_strdel(&g_env[i]);
		g_env[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
