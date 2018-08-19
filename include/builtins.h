/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 04:28:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/19 09:16:26 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "./extension.h"
#include "./stdin.h"

# define BI_MAX 4084
# define MAX_HASH 100

typedef enum	e_bierror
{
	NOBIERROR,
	BIFLAG,
	BINOFOUND,
	BITOMANY,
	BITOFEW,
	BIEQUAL
}				t_bierror;

typedef struct			s_hashcase
{
	int					hits;
	char				*command;
	char				*raccmd;
	struct s_hashcase	*next;
}						t_hashcase;

typedef struct			s_hashtable
{
	int					key;
	t_hashcase			*hashcase;
}						t_hashtable;

/*
*******************************************************************************
**					builtins_errors.c
*******************************************************************************
*/

int				ft_bierrors(const char *prgm, const char *cmd, t_bierror err);

/*
*******************************************************************************
**					ft_env.c
*******************************************************************************
*/

int				ft_env(t_op *exec);

/*
*******************************************************************************
**					ft_set_unset_env.c
*******************************************************************************
*/

int				ft_setenv(const char *name, const char *value);
int				ft_unsetenv(const char *name);

/*
*******************************************************************************
**					ft_env_tools.c
*******************************************************************************
*/

char			*ft_envset_line(const char **envset, const char *name);
char			*ft_envset_value(const char **envset, const char *name);
char			*ft_envset_join(const char *name, const char *value);

/*
*******************************************************************************
**					ft_cd.c
*******************************************************************************
*/

int				ft_cd(t_op *t_exec, int flag);

/*
*******************************************************************************
**					ft_echo.c
*******************************************************************************
*/

int				ft_echo(t_op *t_exec, int flag);

/*
*******************************************************************************
**					ft_exit.c
*******************************************************************************
*/

int				ft_exit(t_op *t_exec, int flag);

/*
*******************************************************************************
					ft_hashtable.c
*******************************************************************************
*/

void			ft_hashtable(char *cmd, char *raccmd);
int				ft_hash(const char *cmd);
void			ft_hash_print(t_hashtable *hashtable);

/*
*******************************************************************************
					ft_hashtable_manage.c
*******************************************************************************
*/

t_hashtable		*ft_hashtable_create(void);
t_hashcase		*ft_create_case(const char *cmd, const char *raccmd);
void			ft_save_hash(t_hashtable **hashtable);
void			ft_hash_add(t_hashcase **begin, t_hashcase *hashcase);

#endif
