/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 06:30:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 04:48:36 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

char		*ft_get_var(char *line)
{
	int		i;

	i = 0;
	if (line)
		while (line[i])
		{
			if (line[i] == '=')
				return (ft_strsub(line, 0, i));
			i++;
		}
	return (NULL);
}

char		*ft_get_value(char *line)
{
	int		i;

	i = 0;
	if (line)
		while (line[i])
		{
			if (line[i] == '=' && line[i] + 1)
				return (ft_strdup(line + (i + 1)));
			i++;
		}
	return (NULL);
}
