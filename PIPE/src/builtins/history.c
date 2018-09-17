/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 02:27:55 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/16 09:44:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		save_to_file(char **histsave, char *path)
{
	int		fd;
	int		i;

	i = -1;
	fd = -1;
	if (histsave)
	{
		if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
			return (EXIT_FAILURE);
		while (histsave[++i])
			ft_putendl_fd(histsave[i], fd);
		return (close(fd) == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int		add_memory(char **ret, char *news)
{
	char	*tmp;

	tmp = ft_strjoin("[", news);
	*ret = ft_strjoin(tmp, "]");
	ft_strdel(&tmp);
	return (0);
}

void			history_save(char ***history, char *news, int version, char *s)
{
	static char		**histsave = NULL;
	static char		*path = NULL;
	char			*tmp;

	tmp = NULL;
	if (version == -1)
	{
		int i = 0;
		if (*history)
			while ((*history)[i])
			{
				printf("HISTORY[%d] == %s\n", i, (*history)[i]);
				i++;
			}
		path = ft_strdup(s);
		histsave = ft_tabdup(*history);
	}
	else if (version == 0 && histsave)
		*history = histsave;
	else if (version == 1)
	{
		add_memory(&tmp, news);
		ft_malloc_cmd(&histsave, tmp);
	}
	else if (version == 2)
	{
		tmp = ft_strjoin(path, "/.101sh_history");
		save_to_file(histsave, tmp);
		ft_tabdel(&histsave);
		ft_strdel(&path);
		ft_strdel(&tmp);
	}
}

static char		*made_history(char *str)
{
	char		*ret;
	int			i;
	int			j;

	j = 0;
	i = 0;
	ret = NULL;
	if (str)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
			return (NULL);
		while (str[i])
		{
			if (i != 0 && str[i + 1])
				ret[j++] = str[i];
			i++;
		}
		ret[j] = '\0';
	}
	return (ret);
}

void			history_get(char **line, int index)
{
	char		**history;
	int			i;

	i = 0;
	history = NULL;
	history_save(&history, NULL, 0, (char *)NULL);
	ft_reverse_tab(&history);
	printf("CALL HISTORY\n");
	fflush(NULL);
	if (history)
	{
		while (history[i] && i <= index)
		{
			printf("HIST[%d] == %s\n", i, history[i]);
			if (*line && !ft_strncmp(*line, history[i], ft_strlen(*line) - 1))
			{
				ft_strdel(line);
				*line = made_history(history[i]);
			}
			else if (!*line && (i == index || !history[i + 1]))
				*line = made_history(history[i]);
			i++;
		}
	}
	printf("FINISH HISTORY\n");
}
