#include "../../include/execute.h"
#include "../../include/stdin.h"

static void		ft_skip_n(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}
void	ft_read_line(int fd, char *s)
{
	char	line[100];
	char	*list[100];
	int		i;
	e_prompt	prompt;

	prompt = E_HDOC;
	display_prompt(NULL, prompt);
	ft_bzero(line, 100);
	ft_bzero(list, 100 * sizeof(*list));
	i = 0;
	while (read(1, line, 4096) > 0)
	{
		ft_skip_n(line);
		if (ft_strcmp(line, s) == 0)
			break ;
		else
		{
			display_prompt(NULL, prompt);
			ft_strcat(line, "\n");
			list[i++] = ft_strdup(line);
		}
		ft_bzero(line, 100);
	}
	i = -1;
	while (list[++i])
		ft_putstr_fd(list[i], fd);
}

int		ft_heredoc(t_op *t_exec, char *bin, int flag, int bfd)
{
	int fd[2];
	int ok;

	pipe(fd);
	ft_read_line(fd[1], t_exec->redirect->file);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		if (ft_builtins(t_exec, ok, flag) == 0)
			return (0);
		else
			return (2);
	}
	else
	{
		if (ft_exec(t_exec, bin, flag, bfd) == 0)
			return (0);
		else
			return (2);
	}
}

int				ft_redirect_heredoc(t_op *t_exec, int flag)
{
	char		*tmp_bin;
	pid_t		pid;
	int			stat;

	tmp_bin = ft_search_bin(t_exec->cmd[0]);
	if ((pid = fork()) < 0)
		exit(1);
	else if (pid == 0)
	{
		if (ft_heredoc(t_exec, tmp_bin, flag, -12) == 0)
			;
		else
			return (2);
	}
	else
	{
		wait(&stat);
		if (WIFEXITED(stat))
		{
			if (WEXITSTATUS(stat) != 0)
				return (0);
		}
		return (0);
	}
	return (0);
}
