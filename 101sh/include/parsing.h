/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:32:44 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 10:07:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/include/libft.h"
#include "./lexer.h"

typedef struct					s_arg
{
	char						**cmd;//COMMANDE COMPLETE
	e_token						not_operator;//AU CAS OU !CMD
	e_token						token[2];// token > SEMI && token < DLESSDASH
	struct s_arg				*next;
	struct s_arg				*prev;
}								t_arg;

typedef struct					s_sc
{
	char						**cmd;//COMMANDE COMPLETE
	e_token						not_operator;//AU CAS OU !CMD
}								t_sc;

typedef struct					s_cc
{
	e_token				key;//Mot cle tels que "IF" "ELSE" "ELIF" "CASE" "WHILE" "UNTIL" "FOR"
	e_token				not_operator;// AU CAS OU "! KEY"
	t_arg				*arg;
	int					open_key;//DO THEN REPERER
	int					close_key;//FI DONE ESAC REPERER
	struct s_cc			*next_in;
	struct s_cc			*next_out;
	struct s_cc			*parent;
}								t_cc;

typedef struct					s_op
{
	e_token						token[2];//PIPE, LOGICAL REDIRECTION OPERATOR
	t_sc						*sc;//commande sans mot cle(simple commande)
	t_cc						*cc;//commande comprenant un mot cle(commande compose)
	struct s_op					*next;//SUITE DE L'OPERATEUR
	struct s_op					*prev;
}								t_op;

typedef struct					s_seq
{
	e_token						token; // LIST TERMINATOR
	t_op						*op;
	struct s_seq				*next;
	struct s_seq				*prev;
}								t_seq;

t_seq							*ft_manage_parsing(t_lex lex);
/*
typedef struct		s_word
{
	char			*name;
	e_token			token;
	s_word			*next;
}					t_word;

typedef struct		s_command
{
	e_token			token; // && || | ;

	struct cmd		*next;
}					t_command;

typedef struct		s_sequence
{
	e_token			token; // ; ou &
	struct s_cmd	cmd*;
	struct s_seq	*next;
}				t_sequence;
*/
