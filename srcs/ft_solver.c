/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_solver.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 12:33:01 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 16:38:02 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_solver_init(t_token *token, char *arg[100])
{
	t_token		*p;
	int			i;

	i = -1;
	while (arg[++i] && (i < 100))
		ft_strdel(&arg[i]);
	while (arg[i] && (i < 100))
		arg[i++] = NULL;
	p = token->cmdarg;
	arg[0] = ft_strdup(token->id);
	i = 0;
	while (p)
	{
		arg[++i] = ft_strdup(p->id);
		p = p->next;
	}
	arg[++i] = NULL;
}

static int		ft_solver_bi_error(t_token *token, char *arg[100])
{
	if (ft_strcmp(token->id, "cd") == 0 && arg[2] != NULL)
		return (ft_error_cd("", 1));
	else if (ft_strcmp(token->id, "setenv") == 0)
	{
		if (arg[1] == NULL)
			return (ft_error_env("", 1));
		else if (ft_strrchr(arg[1], '='))
			return (ft_error_env("", 2));
		else if (arg[3] != NULL)
			return (ft_error_env("", 3));
	}
	else if (ft_strcmp(token->id, "unsetenv") == 0)
		if (arg[1] == NULL)
			return (ft_error_env("", 4));
	return (0);
}

static int		ft_solver_bi(t_token *token, char *arg[100])
{
	int			i;

	if (ft_solver_bi_error(token, arg))
		return (1);
	if (ft_strcmp(token->id, "cd") == 0)
		i = ft_builtin_cd(arg[1]);
	else if (ft_strcmp(token->id, "env") == 0)
		i = ft_builtin_env();
	else if (ft_strcmp(token->id, "setenv") == 0)
		i = ft_builtin_setenv(arg[1], arg[2]);
	else if (ft_strcmp(token->id, "unsetenv") == 0)
		i = ft_builtin_unsetenv(arg[1]);
	else if (ft_strcmp(token->id, "exit") == 0)
		i = ft_builtin_exit(token, arg);
	else
		i = ft_builtin_echo(arg);
	return (i);
}
static int		ft_solver_output(t_token *token, char *arg[100], char *file, int flag)
{
	int			i;
	if (ft_solver_bi_error(token, arg))
		return (1);
	printf("======> %d\n", flag);
	if (ft_strcmp(token->id, "cd") == 0)
		i = ft_builtin_cd_redirect(arg[1], file, flag);
	if (ft_strcmp(token->id, "env") == 0)
		i = ft_builtin_env_output(file, flag);
	/*else if (ft_strcmp(token->id, "setenv") == 0)
	  i = ft_builtin_setenv(arg[1], arg[2]);
	  else if (ft_strcmp(token->id, "unsetenv") == 0)
	  i = ft_builtin_unsetenv(arg[1]);
	  else if (ft_strcmp(token->id, "exit") == 0)
	  i = ft_builtin_exit(token, arg);*/
	if (ft_strcmp(token->id, "echo") == 0)
		i = ft_builtin_echo_output(arg, token, file, flag);
	return (i);
}



static int		ft_solver_cmd(char *arg[100])
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;

	ret = 0;
	cmd = ft_strdup(arg[0]);
	ft_strdel(&arg[0]);
	arg[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	if ((cpid = fork()) == 0)
	{
		if (execve(cmd, arg, g_env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	cmd ? ft_strdel(&cmd) : 0;
	if (ret == 1)
		return (1);
	return (0);
}

int			ft_redirect_output(t_token *tok, char *arg[100], char *file, int flag)
{
	t_token *tmptock;
	pid_t		cpid;
	int i = 1;
	char		*cmd;
	int flag2;
	int ret;

	if (flag == O_RDONLY)
	{
		printf("PUTA CABAN\n");
		flag2 = O_RDONLY;
	}
	else
		flag2 = O_WRONLY;
	printf("======> %d\n", flag);
	tmptock = tok;
	cmd = ft_strdup(arg[0]);
	ft_strdel(&arg[0]);
	arg[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	cpid = fork();
	if (cpid > 0)
		wait(0);
	else
	{
		i = 1;
		if (flag2 != O_RDONLY)
			ret = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if (flag2 == O_RDONLY)
			ret = open(file, O_RDONLY);

		if (ret == -1)
		{
			ft_putendl("Error");
		}
		if (flag2 == O_RDONLY)
			dup2(ret, 0);
		else
			dup2(ret, 1);
		execve(cmd, arg, g_env);
		close(ret);
	}
	return (0);
}

int				ft_return_flag(char *one, int dd)
{
	if (ft_strcmp(one, ">") == 0)
		return (O_APPEND);
	if (ft_strcmp(one, "<") == 0)
	{
		printf("OK\n");
		return (O_RDONLY);
	}
	if (dd == 1)
		return (O_RDONLY);
	else
		return (O_TRUNC);


}
int				ft_solver(t_token *tbegin)
{
	t_token		*token;
	int			i;
	char		*arg[100];
	int 		o;
	int ok = 0;
	int co;
	char *file;
	int flag;
	int flag2;
	int f;

	i = 0;
	o = 0;
	co = 1;
	arg[0] = NULL;
	while (tbegin)
	{
		co++;
		token = tbegin;
		ft_solver_init(token, arg);
		if (token->type == BI)
		{
			if (token->next != NULL)
			{
				if (ft_return_flag(token->next->id, 0) == O_APPEND || ft_return_flag(token->next->id, 0) == O_RDONLY)
				{
					ok = 1;
					flag2 = ft_return_flag(token->next->id, 0);

					if ((flag = ft_return_flag(token->next->next->id, 0)) == O_APPEND)
						file = token->next->next->next->id;
					if ((flag = ft_return_flag(token->next->next->id, 0)) == O_RDONLY)
						file = token->next->next->next->id;
					else
						file = token->next->next->id;
					i = ft_solver_output(token, arg,file, flag);
				}
			}
			else
				i = ft_solver_bi(token, arg);
		}
		else if (token->type == ID)
		{
			if (token->next != NULL)
			{
				if (ft_return_flag(token->next->id, 0) == O_APPEND || ft_return_flag(token->next->id, 0) == O_RDONLY)
				{
					ok = 1;
					o = 1;
					flag2 = ft_return_flag(token->next->id, 0);
					if(flag2 == O_RDONLY)
						f = 1;
					else
						f = 0;
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_APPEND)
						file = token->next->next->next->id;
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_RDONLY)
					{
						printf("YEAH %s\n", token->next->next->id);
						if (f == 1)
							file = token->next->next->id;
						else
							file = token->next->next->next->id;

					}
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_TRUNC)
						file = token->next->next->id;
					i = ft_redirect_output(token, arg, file, flag);
				}
			}
			else if (ok == 0)
				i = ft_solver_cmd(arg);
		}
		else if (token->type == NONE && ok == 0)
		{
			i = ft_error_none(arg[0]);
		}
		ft_lexer_del(arg);
		tbegin = tbegin->next;
	}
	return (i);
}
