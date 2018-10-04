/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 06:07:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 08:10:15 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		ft_isdir(char *test)
{
	struct stat		stat;

	if (lstat(test, &stat) != -1 && (stat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int		issep(const char *s, int i)
{
	if (ft_isseparator(s[i]) && (i == 0 || (i > 0 && s[i - 1] != '\\')))
		return (1);
	return (0);
}

int		ft_isechap(char c)
{
	if (c == '$' || c == ' ' || c == '/' || c == '*'|| c == '\'' || c == '"' ||
		c == '`' || c == '#' || c == '&' || c == '<' || c == '>' || c == ';' ||
		c == '|' || c == '!' || c == '?' || c == '\\' || c == '~')
		return (1);
	return (0);
}

int		ft_isseparator(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

char	*ft_search_pwd(char *ext)
{
	char	*ret;
	char	pwd[4096];
	char	*tmp;

	ret = NULL;
	getcwd(pwd, sizeof(pwd));
	if (ext)
	{
		tmp = ft_strjoin(pwd, "/");
		ret = ft_strjoin(tmp, ext);
		ft_strdel(&tmp);
	}
	else
		ret = ft_strdup(pwd);
	return (ret);
}

char	*ft_search_absolute_path(char *line)
{
	int		i;
	char	*absolute_path;

	i = ft_strlen(line) - ft_strlen(ft_strrchr(line, '/'));
	absolute_path = ft_strsub(line, 0, line[1] ? i : 1);
//	printf("ABSOLUTE == %s\n", absolute_path);
	return (absolute_path);
}

char	*ft_search_relative_path(char *line)
{
	char	*relative_path;
	char	*tmp;
	int		i;

	i = ft_strlen(line) - ft_strlen(ft_strrchr(line, '/'));
	tmp = ft_strsub(line, 0, i);
	relative_path = ft_search_pwd(tmp);
	ft_strdel(&tmp);
	return (relative_path);
}

char	*ft_search_path(char *line)
{
	char	*pwd;

	if (!line || !ft_strchr(line, '/'))
	{
//		printf("000\n");
		pwd = ft_search_pwd(NULL);
	}
	else if (ft_strchr(line, '/') && !(line[0] == '/'))
	{
//		printf("111\n");
		pwd = ft_search_relative_path(line);
	}
	else
	{
//		printf("222\n");
		pwd = ft_search_absolute_path(line);
	}
	return (pwd);
}

int		ft_cut_word_and_before(char **str, char *word, char **before)
{
	int		i;

	if (word && word[ft_strlen(word) - 1] != '/' && ft_strchr(word, '/'))
	{
		*str = ft_strdup(ft_strrchr(word, '/') + 1);
		i = ft_strlen(word) - ft_strlen(*str);
		*before = ft_strsub(word, 0, i);
//	printf("BEFORE == %s\n", *before);
//	sleep(2);
	}
	else if (!ft_strchr(word, '/'))
	{
		*str = ft_strdup(word);
	}
	else
	{
		*before = ft_strdup(word);
		ft_strdel(str);
	}
	return (0);
}

int		is_more_long(t_editor **ed)
{
	int		tmp;

	tmp = (*ed)->t.nb_line;
	(*ed)->t.nb_line = ((*ed)->prompt_size +
	((*ed)->line ? ft_strlen((*ed)->line) : 0)) / (*ed)->ws_col + 1;
	if (tmp != 0 && tmp != (*ed)->t.nb_line)
		return (1);
	return (0);
}
