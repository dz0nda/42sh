/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_term_init.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/12 04:45:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:37:15 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int			add_info_params(int ac, char **av)
{
	char	*tmp;
	int		i;
	char	*etoile;

	tmp = NULL;
	i = -1;
	etoile = NULL;
	while (av[++i])
	{
		tmp = ft_itoa(i);
		add_to_set(tmp, av[i]);
		ft_strdel(&tmp);
		if (etoile)
		{
			tmp = ft_strjoin(etoile, "\n");
			ft_strdel(&etoile);
			etoile = ft_strjoin(tmp, av[i]);
			ft_strdel(&tmp);
		}
		else
			etoile = ft_strdup(av[i]);
	}
	add_to_set("*", etoile);
	ft_strdel(&etoile);
	return (EXIT_SUCCESS);
}

static void			add_info_id(void)
{
	char	*str;
	char	buff[BUFF_SIZE];

	str = NULL;
	ft_bzero(buff, BUFF_SIZE);
	if ((str = ft_itoa(getppid())))
		add_to_set("PPID", str);
	ft_strdel(&str);
	if ((str = ft_itoa(getuid())))
		add_to_set("UID", str);
	ft_strdel(&str);
	if ((str = ft_itoa(geteuid())))
		add_to_set("EUID", str);
	ft_strdel(&str);
	if ((gethostname(buff, sizeof(buff))) == 0)
		add_to_set("HOSTNAME", buff);
}

static int				manage_info_history(char *av)
{
	char	*path;
	char	*str;
	int		fd;
	int		i;

	path = NULL;
	str = NULL;
	fd = -1;
	i = 0;
	add_to_set("HISTSIZE", "500");
	path = search_path_of_101sh(av);
	if (access((str = ft_strjoin(path, "/.101sh_history")), F_OK) == 0)
	{
		add_to_set("HISTFILE", str);
		fd = open(str, O_RDONLY);
		ft_strdel(&str);
		while (get_next_line(fd, &str) > 0 && ++i)
			ft_strdel(&str);
		close(fd);
		add_to_set("HISTFILESIZE", (str = ft_itoa(i)));
		ft_strdel(&str);
		ft_strdel(&path);
		return (EXIT_SUCCESS);
	}
	add_to_set("HISTFILESIZE", "NULL");
	add_to_set("HISTFILE", "UNKNOW");
	ft_strdel(&str);
	ft_strdel(&path);
	return (EXIT_SUCCESS);
}

static int			get_sysname(int ac)
{
	char			*tmp;
	struct utsname	t_utsname;
	struct stat		statbuf;
	struct passwd	*pwd;

	tmp = NULL;
	ft_memset(&t_utsname, 0, sizeof(struct utsname));
	ft_memset(&statbuf, 0, sizeof(struct stat));
	pwd = NULL;
	if ((uname(&t_utsname)) == 0)
		add_to_set("SYSNAME", t_utsname.sysname);
	if ((tmp = ft_itoa(ac)))
		add_to_set("#", tmp);
	ft_strdel(&tmp);
	if ((tmp = ft_itoa(getpid())))
	{
		add_to_set("PID", tmp);
		add_to_set("$", tmp);
	}
	ft_strdel(&tmp);
	return (0);
}

int					init_set(int ac, char **av)
{
	if (g_env)
		g_set = ft_tabdup(g_env);
	add_info_params(ac, av);
	add_info_id();
	add_to_set("IFS", " \t\n");
	manage_info_history(av[0]);
	get_sysname(ac);
	return (EXIT_SUCCESS);
}
