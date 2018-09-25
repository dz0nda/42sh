/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt_git.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay  <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/22 19:04:02 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 05:29:26 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static char    *ft_miniconcat(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

static	char        *ft_check_git_config(char *path)
{
	int        fd;
	char    *line;

	path = ft_miniconcat(path, "/config");
	free(path);
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp("[branch ", line, 8))
		{
			line[ft_strlen(line) - 2] = '\0';
			path = ft_strdup(line + 9);
			free(line);
			close(fd);
			return (path);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (NULL);
}

static	char        *ft_get_git_branch()
{
	int        i;
	char    cwd[1024];
	char    *path;

	getcwd(cwd, 1024);
	path = ft_strdup(cwd);
	path = ft_miniconcat(path, "/.git");
	i = ft_strlen(path);
	while (path[--i])
	{
		if (path[i] == '/' && ft_strcmp(path + i, ".git"))
		{
			path[i] = '\0';
			path = ft_miniconcat(path, "/.git");
		}
		if (!access(path, F_OK))
			return (ft_check_git_config(path));
	}
	free(path);
	return (NULL);
}

void				ft_print_git_branch(void)	
{
	char    *prompt;
	char    *git_branch;

	prompt = ft_strdup("\e[94mgit:(\e[95m");
	git_branch = ft_get_git_branch();
	prompt = ft_miniconcat(prompt, git_branch);
	free(git_branch);
	prompt = ft_miniconcat(prompt, "\e[94m)\e[0m ");
	ft_putstr(prompt);
	free(prompt);
}